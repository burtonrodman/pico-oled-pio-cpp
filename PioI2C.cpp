#include <stdio.h>
#include "pico/stdlib.h"

#include "I2C.h"
#include "PioI2C.h"
#include "pio_i2c.h"
#include "pio_i2c.c"


PioI2C::PioI2C(
    uint8_t scl,
    uint8_t sda,
    uint32_t freq,
    PIO pio
) {
    _scl = scl; 
    _sda = sda;
    _freq = freq;
    _pio = pio;
}

PioI2C::~PioI2C() { }

uint PioI2C::init() {
    printf("in PioI2C::init\n");

    uint offset = pio_add_program(pio0, &i2c_program);
    i2c_program_init(pio0, 0, offset, 16, 17);
    
    printf("PioI2C::init done\n");
    return 0;
}

int PioI2C::write_blocking(
    uint8_t addr,
    uint8_t* src,
    uint len,
    bool nostop
) {
    int err = pio_i2c_write_blocking(pio0, 0u, addr, src, len);
    if (err < 0) {
        printf("!");
        return err;
    } else {
        printf(".");
        return len;
    }
}