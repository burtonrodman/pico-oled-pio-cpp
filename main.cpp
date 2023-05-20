#include <stdio.h>
#include <cstring>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/multicore.h"
#include "hardware/irq.h"

// USB
#include "tusb.h"
#include "bsp/board.h"
#include "class/midi/midi_host.h"

// NETWORK
// #include "lwip/dns.h"
// #include "lwip/ip4_addr.h"
// #include "lwip/sockets.h"

// #include "blink_led.h"

#include "renderer/Renderer.h"

const char ssid[] = "<ssid>";
const char pass[] = "<password>";

#include "XTouchMini.h"

using namespace std;

static uint8_t midi_dev_addr = 0;
static MixerModel* mixer;

static void poll_usb_rx(bool connected)
{
    // device must be attached and have at least one endpoint ready to receive a message
    if (!connected || tuh_midih_get_num_rx_cables(midi_dev_addr) < 1)
    {
        return;
    }
    tuh_midi_read_poll(midi_dev_addr);
}

void core1_entry() {
    const uint offset0 = pio_add_program(pio0, &i2c_program);
    const uint offset1 = pio_add_program(pio1, &i2c_program);

    mixer = createMixerModel();
    std::vector<Renderer*> renderers = createRenderers(mixer, offset0, offset1);

    uint8_t x = 1;
    while (1) {
        for (Renderer* renderer : renderers) {
            renderer->render();
        }
    }
}

void ensure_wifi_connected() {

    static int cycle = 0;

    if (cycle % 256 == 0) {
        auto status = cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA);
        mixer->System->WifiLinkStatus = status;
        mixer->System->Dirty = true;

        switch (status)
        {
        case CYW43_LINK_DOWN:
        case CYW43_LINK_FAIL:
        case CYW43_LINK_NONET:
        case CYW43_LINK_BADAUTH:
            mixer->System->WifiConnected = false;
            mixer->System->WifiConnectError = cyw43_arch_wifi_connect_async(ssid, pass, CYW43_AUTH_WPA2_AES_PSK);
            break;

        case CYW43_LINK_JOIN:
        case CYW43_LINK_NOIP:
            mixer->System->WifiConnected = false;
            mixer->System->WifiConnectError = 0;
            break;

        case CYW43_LINK_UP:
            mixer->System->WifiConnected = true;
            // char *ipAddr = ipaddr_ntoa(netif_ip4_addr(&cyw43_state.netif[0]));
            // mixer->System->IpAddress = std::string(ipAddr);
            break;
        
        default:
            break;
        }
        mixer->System->Dirty = true;
    }

    cycle++;

}

int main() {
    stdio_init_all();

    // TinyUSB
    board_init();
    tusb_init();

    multicore_launch_core1(core1_entry);

    if (cyw43_arch_init_with_country(CYW43_COUNTRY_USA))
    {
        printf("Wifi init failed");
        return -1;
    }
    // cyw43_wifi_pm(&cyw43_state, CYW43_PERFORMANCE_PM);

    cyw43_arch_enable_sta_mode();

    printf("waiting for MIDI events\n");
    while (1) {
        tuh_task();

        ensure_wifi_connected();

        // blink_led();
        if (midi_dev_addr != 0 && tuh_midi_configured(midi_dev_addr)) {
            tuh_midi_stream_flush(midi_dev_addr);
            poll_usb_rx(true);
        }
    }

    return 0;
}

// void tcp_setup(void) {
//     struct ip_addr ip;
//     IP4_ADDR(&ip, 10, 0, 0, 231);

//     testpcb = tcp_new();

//     uint32_t data = 0xdeadbeef;
//     tcp_arg(testpcb, &data);

//     tcp_error(testpcb, tcpErrorHandler);
//     tcp_recv(testpcb, tcpRecvCallback);
//     tcp_sent(testpcb, tcpSendCallback);

//     tcp_connect(testpcb, &ip, 5086, connectCallback);
// }

// uint32_t tcp_send_packet(void) {
//     char *string = "HEAD /random HTTP/1.0\r\n\r\n ";
//     uint32_t len = strlen(string);

//     /* push to buffer */
//     error = tcp_write(testpcb, string, strlen(string), TCP_WRITE_FLAG_COPY);

//     if (error) {
//         // UARTprintf("ERROR: Code: %d (tcp_send_packet :: tcp_write)\n", error);
//         return 1;
//     }

//     /* now send */
//     error = tcp_output(testpcb);
//     if (error) {
//         // UARTprintf("ERROR: Code: %d (tcp_send_packet :: tcp_output)\n", error);
//         return 1;
//     }
//     return 0;
// }

// err_t tcpRecvCallback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
// {
//     // UARTprintf("Data recieved.\n");
//     if (p == NULL) {
//         // UARTprintf("The remote host closed the connection.\n");
//         // UARTprintf("Now I'm closing the connection.\n");
//         tcp_close_con();
//         return ERR_ABRT;
//     } else {
//         // UARTprintf("Number of pbufs %d\n", pbuf_clen(p));
//         // UARTprintf("Contents of pbuf %s\n", (char *)p->payload);
//         mixer->System->IpAddress = std::string(p->payload)
//     }

//     return 0;
// }

//--------------------------------------------------------------------+
// TinyUSB Callbacks
//--------------------------------------------------------------------+

// Invoked when device with hid interface is mounted
// Report descriptor is also available for use. tuh_hid_parse_report_descriptor()
// can be used to parse common/simple enough descriptor.
// Note: if report descriptor length > CFG_TUH_ENUMERATION_BUFSIZE, it will be skipped
// therefore report_desc = NULL, desc_len = 0
void tuh_midi_mount_cb(uint8_t dev_addr, uint8_t in_ep, uint8_t out_ep, uint8_t num_cables_rx, uint16_t num_cables_tx)
{
//   printf("MIDI device address = %u, IN endpoint %u has %u cables, OUT endpoint %u has %u cables\r\n",
//       dev_addr, in_ep & 0xf, num_cables_rx, out_ep & 0xf, num_cables_tx);

  if (midi_dev_addr == 0) {
    // then no MIDI device is currently connected
    midi_dev_addr = dev_addr;
  }
//   else {
//     printf("A different USB MIDI Device is already connected.\r\nOnly one device at a time is supported in this program\r\nDevice is disabled\r\n");
//   }
}

// Invoked when device with hid interface is un-mounted
void tuh_midi_umount_cb(uint8_t dev_addr, uint8_t instance)
{

  if (dev_addr == midi_dev_addr) {
    midi_dev_addr = 0;
    // printf("MIDI device address = %d, instance = %d is unmounted\r\n", dev_addr, instance);
  }
//   else {
//     printf("Unused MIDI device address = %d, instance = %d is unmounted\r\n", dev_addr, instance);
//   }
}

void tuh_midi_rx_cb(uint8_t dev_addr, uint32_t num_packets)
{
    if (midi_dev_addr == dev_addr && num_packets != 0)
    {
        uint8_t cable_num;
        uint8_t buffer[48];
        while (1) {
            uint32_t bytes_read = tuh_midi_stream_read(dev_addr, &cable_num, buffer, sizeof(buffer));
            if (bytes_read == 0)
                return;
            if (cable_num == 0) {
                // TODO - move me to the main core0 loop as a fifo read so that the "business logic" has a say in what gets written back
                uint32_t nwritten = tuh_midi_stream_write(dev_addr, cable_num, buffer, bytes_read);

                mixer->DispatchMidiMessage(buffer, bytes_read);
            }
        }
    }
}

void tuh_midi_tx_cb(uint8_t dev_addr)
{
    // (void)dev_addr;
}