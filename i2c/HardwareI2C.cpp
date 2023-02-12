#include <cstdio>
#include "pico/stdlib.h"

#include "hardware/i2c.h"

#include "I2C.h"
#include "HardwareI2C.h"

HardwareI2C::HardwareI2C(
    uint8_t scl,
    uint8_t sda,
    uint32_t freq,
    i2c_inst_t* i2c
) {
    _scl = scl; 
    _sda = sda;
    _freq = freq;
    _i2c = i2c;
}

HardwareI2C::~HardwareI2C() {
    printf("in HardwareI2C::~HardwareI2C\n");
    i2c_deinit(_i2c);
}

uint HardwareI2C::init() {
    printf("in HardwareI2C::init, sda=%d, scl=%d\n", _sda, _scl);
    uint actualbaud = i2c_init(i2c0, 400 * 1000);

    gpio_set_function(_sda, GPIO_FUNC_I2C);
    gpio_set_function(_scl, GPIO_FUNC_I2C);

    gpio_pull_up(_sda);
    gpio_pull_up(_scl);

    return actualbaud;
}

int HardwareI2C::write_blocking(
    uint8_t addr,
    uint8_t* src,
    uint len,
    bool nostop
) {
    int written = i2c_write_blocking(_i2c, addr, src, len, nostop);
    if (written == PICO_ERROR_GENERIC) {
        printf("!");
    } else {
        printf(".");
    }
    return written;
}