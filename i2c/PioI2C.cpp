#include <cstdio>
#include "pico/stdlib.h"

#include "I2C.h"
#include "PioI2C.h"
#include "pio_i2c.h"
#include "pio_i2c.c"


PioI2C::PioI2C(
    PIO pio,
    uint sm,
    uint program_offset,
    uint scl,
    uint sda,
    uint32_t freq
) {
    _pio = pio;
    _sm = sm;
    _program_offset = program_offset;
    _scl = scl; 
    _sda = sda;
    _freq = freq;
}

PioI2C::~PioI2C() { }

uint PioI2C::init() {
    i2c_program_init(_pio, _sm, _program_offset, _sda, _scl);
    
    return 0;
}

int PioI2C::write_blocking(
    uint8_t addr,
    uint8_t* src,
    uint len,
    bool nostop
) {
    static int writecnt;

    writecnt++;
    int err = pio_i2c_write_blocking(_pio, _sm, addr, src, len);
    if (err < 0) {
        printf("!");
        return err;
    } else {
        if (writecnt % 10 == 0)
            printf(".");
        return len;
    }
}