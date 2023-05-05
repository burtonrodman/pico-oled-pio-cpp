#include <stdio.h>
#include <cstring>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/multicore.h"
#include "hardware/irq.h"

#include "tusb.h"
#include "bsp/board.h"
#include "class/midi/midi_host.h"

// #include "blink_led.h"

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

// void core1_interrupt_handler() {
//     while (multicore_fifo_rvalid()) {
//         uint32_t message = multicore_fifo_pop_blocking();

//         uint8_t buffer[4] = {
//             (uint8_t) ( message & 0x000000ff       ),
//             (uint8_t) ((message & 0x0000ff00) >> 8 ),
//             (uint8_t) ((message & 0x00ff0000) >> 16),
//             (uint8_t) ((message & 0xff000000) >> 24)           
//         };
//     }
//     multicore_fifo_clear_irq();
// }

void core1_entry() {
    // multicore_fifo_clear_irq();
    // irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_interrupt_handler);
    // irq_set_enabled(SIO_IRQ_PROC1, true);

    const uint offset0 = pio_add_program(pio0, &i2c_program);
    const uint offset1 = pio_add_program(pio1, &i2c_program);

    mixer = createMixerModel();
    std::vector<Renderer*> renderers = createRenderers(mixer->Channels, offset0, offset1);

    uint8_t x = 1;
    while (1) {

        // mixer->Channels[0]->EncoderValue = x++;
        mixer->Channels[0]->lastMidiMessage[2] = x;
        mixer->Channels[0]->Dirty = true;

        for (Renderer* renderer : renderers) {
            renderer->render();
        }
    }
}

int main() {
    stdio_init_all();

    // TinyUSB
    board_init();
    tusb_init();

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

    multicore_launch_core1(core1_entry);

    printf("waiting for MIDI events\n");
    while (1) {
        tuh_task();

        // blink_led();
        if (midi_dev_addr != 0 && tuh_midi_configured(midi_dev_addr)) {
            tuh_midi_stream_flush(midi_dev_addr);
            poll_usb_rx(true);
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
//   printf("MIDI device address = %u, IN endpoint %u has %u cables, OUT endpoint %u has %u cables\r\n",
//       dev_addr, in_ep & 0xf, num_cables_rx, out_ep & 0xf, num_cables_tx);

//   mixer->Channels[0]->lastMidiMessage[0] = 255;
//   mixer->Channels[0]->lastMidiMessage[1] = 255;
//   mixer->Channels[0]->lastMidiMessage[2] = 255;
//   mixer->Channels[0]->lastMidiMessage[3] = 255;
//   mixer->Channels[0]->Dirty = true;

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
//   mixer->Channels[0]->lastMidiMessage[0] = 0;
//   mixer->Channels[0]->lastMidiMessage[1] = 0;
//   mixer->Channels[0]->lastMidiMessage[2] = 0;
//   mixer->Channels[0]->lastMidiMessage[3] = 0;
//   mixer->Channels[0]->Dirty = true;

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