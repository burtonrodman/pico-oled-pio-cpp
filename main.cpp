#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "tusb.h"
#include "bsp/board.h"
#include "class/midi/midi_host.h"

#include "blink_led.h"

#include "XTouchMini.h"


static uint8_t midi_dev_addr = 0;

static void poll_usb_rx(bool connected)
{
    // device must be attached and have at least one endpoint ready to receive a message
    if (!connected || tuh_midih_get_num_rx_cables(midi_dev_addr) < 1)
    {
        return;
    }
    tuh_midi_read_poll(midi_dev_addr);
}

int main() {
    board_init();
    stdio_init_all();
    // tusb_init();

    if (cyw43_arch_init()) 
    {
        printf("Wifi init failed");
        return -1;
    }

    // pause to allow starting PuTTY
    // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    // sleep_ms(10000);
    // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    // sleep_ms(50);


    const uint offset0 = pio_add_program(pio0, &i2c_program);
    const uint offset1 = pio_add_program(pio1, &i2c_program);

    std::vector<ChannelModel*> channels = createChannelModels();
    std::vector<Renderer*> renderers = createRenderers(channels, offset0, offset1);

    printf("waiting for MIDI events\n");
    int x = 1;
    while (1) {
        // tuh_task();

        blink_led();
        // bool connected = midi_dev_addr != 0 && tuh_midi_configured(midi_dev_addr);

        // if (connected)
        //     tuh_midi_stream_flush(midi_dev_addr);
        // poll_usb_rx(connected);

        x++;
        if (x % 10 == 0) {
            channels[3]->EncoderValue++;
            channels[3]->Dirty = true;
        }

        for (Renderer* renderer : renderers) {
            renderer->render();
        }
    }

    return 0;
}



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
  printf("MIDI device address = %u, IN endpoint %u has %u cables, OUT endpoint %u has %u cables\r\n",
      dev_addr, in_ep & 0xf, num_cables_rx, out_ep & 0xf, num_cables_tx);

  if (midi_dev_addr == 0) {
    // then no MIDI device is currently connected
    midi_dev_addr = dev_addr;
  }
  else {
    printf("A different USB MIDI Device is already connected.\r\nOnly one device at a time is supported in this program\r\nDevice is disabled\r\n");
  }
}

// Invoked when device with hid interface is un-mounted
void tuh_midi_umount_cb(uint8_t dev_addr, uint8_t instance)
{
  if (dev_addr == midi_dev_addr) {
    midi_dev_addr = 0;
    printf("MIDI device address = %d, instance = %d is unmounted\r\n", dev_addr, instance);
  }
  else {
    printf("Unused MIDI device address = %d, instance = %d is unmounted\r\n", dev_addr, instance);
  }
}

void tuh_midi_rx_cb(uint8_t dev_addr, uint32_t num_packets)
{
    if (midi_dev_addr == dev_addr)
    {
        if (num_packets != 0)
        {
            uint8_t cable_num;
            uint8_t buffer[48];
            while (1) {
                uint32_t bytes_read = tuh_midi_stream_read(dev_addr, &cable_num, buffer, sizeof(buffer));
                if (bytes_read == 0)
                    return;
                if (cable_num == 0) {
                    uint32_t nwritten = tuh_midi_stream_write(dev_addr, cable_num, buffer, bytes_read);
                    for (int i = 0; i < bytes_read; i++) {
                        // lastMidiMessage[i] = buffer[i];
                        // printf("%02x ", buffer[i]);
                    }
                }
            }
        }
    }
}

void tuh_midi_tx_cb(uint8_t dev_addr)
{
    (void)dev_addr;
}