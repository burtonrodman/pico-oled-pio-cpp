#include <stdio.h>

#include "I2C.h"
// #include "HardwareI2C.h"
#include "PioI2C.h"
#include "pio_i2c.h"
#include "i2c.pio.h"

#include "OLED.h"
#include "font/Cherry_Cream_Soda_Regular_16.h"

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "MixerModel.h"

int main() {
    stdio_init_all();
    
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

    // SCL, SDA, Width, Height, Frequency, I2C Port
    // printf("creating HardwareI2C\n");
    // HardwareI2C hw(17, 16, 400 * 1000, i2c0);

    printf("creating PioI2C\n");
    PioI2C pio(17, 16, 400 * 1000, pio0);

    printf("assigning hw to i2c pointer\n");
    I2C* i2c = &pio;

    printf("creating OLED\n");
    OLED oled(128, 64, false, i2c);
    // Draw two bitmaps
    // oled.drawBitmap(0, 0, 40, 32, pressure_40x32);
    // oled.drawBitmap(45, 3, 32, 32, temperature_32x32);
    // Draw two circles

    printf("draw circle\n");
    sleep_ms(50);
    oled.drawCircle(100, 16, 14);
    oled.drawFilledCircle(100, 16, 10);
    // Print defaule font string
    uint8_t string1[] = "sup";
    oled.print(0, 35, string1);
    // Print custom font string
    oled.setFont(&Cherry_Cream_Soda_Regular_16);
    uint8_t string2[] = "yo!";
    oled.print(60, 32, string2);
    // Draw a line
    oled.drawFastHLine(0, 60, 128);
    oled.show();
    // Turn scroll ON
    // oled.setScrollDir(true);
    // oled.isScroll(true);

    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(50);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(50);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(50);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(50);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(50);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(1050);
    }
    return 0;
}