#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "../I2C.h"
#include "PioI2C.h"

PioI2C::PioI2C(
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

PioI2C::~PioI2C() {
    // printf("~PioI2C\n");
    // i2c_deinit(_i2c);
}

uint PioI2C::init() {
    // uint actualbaud = i2c_init(i2c0, 400 * 1000);

    // printf("set function\n");
    // gpio_set_function(_sda, GPIO_FUNC_I2C);
    // gpio_set_function(_scl, GPIO_FUNC_I2C);

    // printf("pull up - scl=%d, sda=%d\n", _scl, _sda);
    // gpio_pull_up(_sda);
    // gpio_pull_up(_scl);

    // printf("after pull up \n");

    // return actualbaud;
    return 0;
}

int PioI2C::write_blocking(
    uint8_t addr,
    const uint8_t* src,
    size_t len,
    bool nostop
) {
    // int written = i2c_write_blocking(_i2c, addr, src, len, nostop);
    // if (written == PICO_ERROR_GENERIC) {
    //     printf("!");
    // } else {
    //     printf(".");
    // }
    // return written;
    return 0;
}