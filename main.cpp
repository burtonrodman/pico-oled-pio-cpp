#include <cstdio>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/i2c.h"

#include "OLED.h"
#include "font/Cherry_Cream_Soda_Regular_16.h"

#include "HardwareI2C.h"

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

void drawChannelOled(OLED* oled)
{
    printf("in drawChannelOled\n");
    oled->drawCircle(100, 16, 14);
    oled->drawFilledCircle(100, 16, 10);
    // Print defaule font string
    uint8_t string1[] = "sup";
    oled->print(0, 35, string1);
    // Print custom font string
    oled->setFont(&Cherry_Cream_Soda_Regular_16);
    uint8_t string2[] = "yo!";
    oled->print(60, 32, string2);
    // Draw a line
    oled->drawFastHLine(0, 60, 128);
    oled->show();
}

int main() {
    stdio_init_all();
    
    if (cyw43_arch_init()) 
    {
        printf("Wifi init failed\n");
        return -1;
    }

    // pause to allow starting PuTTY
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(9000);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(50);

    printf("initializing displays\n");

    HardwareI2C hw(17, 16, 400 * 1000, i2c0);
    I2C* i2c = &hw;
    OLED oled(128, 64, false, i2c);

    drawChannelOled(&oled);

    while (1) { blink_led(); }
}

