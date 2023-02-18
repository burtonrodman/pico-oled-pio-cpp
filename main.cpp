#include <stdio.h>

#include "I2C.h"
#include "PioI2C.h"
#include "pio_i2c.h"
#include "i2c.pio.h"

#include "HardwareI2C.h"

#include "OLED.h"
#include "font/Cherry_Cream_Soda_Regular_16.h"

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/util/datetime.h"
#include "hardware/rtc.h"

#include "MixerModel.h"

#include "tusb.h"
#include "bsp/board.h"
#include "class/midi/midi_host.h"

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

static void blink_led(void)
{
    static absolute_time_t previous_timestamp = {0};

    static bool led_state = false;

    absolute_time_t now = get_absolute_time();
    
    int64_t diff = absolute_time_diff_us(previous_timestamp, now);
    if (diff > 1000000) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_state);
        led_state = !led_state;
        previous_timestamp = now;
    }
}

void drawChannelOled(OLED *oled, Channel *chan)
{
    static int x = 0;
    x++;
    x = x % 10;

    oled->clear();
    // char datetime_buf[256];
    // char *datetime_str = &datetime_buf[0];

    // datetime_t current;
    // rtc_get_datetime(&current);
    // datetime_to_str(datetime_str, sizeof(datetime_buf), &current);

    if (chan->EncoderPressed) {
        uint8_t string1[] = "X";
        oled->print(x, 0, string1);
    }
    if (chan->Button1Pressed) {
        uint8_t string2[] = "Y";
        oled->print(x, 16, string2);
    }
    if (chan->Button2Pressed) {
        uint8_t string3[] = "Z";
        oled->print(x, 32, string3);
    }
 
    oled->show();
}

int main() {
    board_init();
    stdio_init_all();
    tusb_init();

    datetime_t t = {
        .year  = 2023,
        .month = 02,
        .day   = 18,
        .dotw  = 5, // 0 is Sunday, so 5 is Friday
        .hour  = 15,
        .min   = 45,
        .sec   = 00
    };
    rtc_init();
    rtc_set_datetime(&t);

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

    printf("initializing displays\n");

    PioI2C pio_u1(pio0, 0u, offset0,  3,  2, 400 * 1000);
    I2C* i2c_u1 = &pio_u1;
    OLED oled_u1(128, 64, false, i2c_u1);
    
    // PioI2C pio_u2(pio0, 1u, offset0, 13, 12, 400 * 1000);
    // I2C* i2c_u2 = &pio_u2;
    // OLED oled_u2(128, 64, false, i2c_u2);
    
    // PioI2C pio_u3(pio0, 2u, offset0, 11, 10, 400 * 1000);
    // I2C* i2c_u3 = &pio_u3;
    // OLED oled_u3(128, 64, false, i2c_u3);
        
    // PioI2C pio_u4(pio0, 3u, offset0,  9,  8, 400 * 1000);
    // I2C* i2c_u4 = &pio_u4;
    // OLED oled_u4(128, 64, false, i2c_u4);

    PioI2C pio_u5(pio1, 0u, offset1,  7,  6, 400 * 1000);
    I2C* i2c_u5 = &pio_u5;
    OLED oled_u5(128, 64, false, i2c_u5);
    
    // PioI2C pio_u6(pio1, 1u, offset1,  5,  4, 400 * 1000);
    // I2C* i2c_u6 = &pio_u6;
    // OLED oled_u6(128, 64, false, i2c_u6);

    // PioI2C pio_u7(pio1, 2u, offset1, 15, 14, 400 * 1000);
    // I2C* i2c_u7 = &pio_u7;
    // OLED oled_u7(128, 64, false, i2c_u7);

    // PioI2C pio_u8(pio1, 3u, offset1, 17, 16, 400 * 1000);
    // I2C* i2c_u8 = &pio_u8;
    // OLED oled_u8(128, 64, false, i2c_u8);


    // HardwareI2C hw_u9(19, 18, 400 * 1000, i2c1);
    // I2C* i2c_u9 = &hw_u9;
    // OLED oled_u9(128, 64, false, i2c_u9);

    // HardwareI2C hw_u10(21, 20, 400 * 1000, i2c0);
    // I2C* i2c_u10 = &hw_u10;
    // OLED oled_u10(128, 64, false, i2c_u10);

    Channel chan1 = {
        0, Single, true, true, true, true, true
    };
    Channel chan2 = {
        0, Single, true, true, true, true, true
    };

    printf("waiting for MIDI events\n");
    while (1) {
        // tuh_task();

        blink_led();
        // bool connected = midi_dev_addr != 0 && tuh_midi_configured(midi_dev_addr);

        // if (connected)
        //     tuh_midi_stream_flush(midi_dev_addr);
        // poll_usb_rx(connected);


        drawChannelOled(&oled_u1, &chan1);
        // drawChannelOled(oled_u2, chan2);
        // drawChannelOled(oled_u3, chan1);
        // drawChannelOled(oled_u4, chan2);
        drawChannelOled(&oled_u5, &chan2);
        // drawChannelOled(oled_u6, chan2);
        // drawChannelOled(oled_u7, chan1);
        // drawChannelOled(oled_u8, chan2);
        // drawChannelOled(oled_u9, chan1);
        // drawChannelOled(oled_u10);
        chan1.Button1Pressed = !chan1.Button1Pressed;
        chan2.Button2Pressed = !chan1.Button2Pressed;

        sleep_ms(100);
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
                    printf("received: ");
                    for (int i = 0; i < bytes_read; i++) {
                        printf("%02x ", buffer[i]);
                    }
                    printf("\n");
                }
            }
        }
    }
}

void tuh_midi_tx_cb(uint8_t dev_addr)
{
    (void)dev_addr;
}