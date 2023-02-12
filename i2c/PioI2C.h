#ifndef _PioI2C_H_
#define _PioI2C_H_

#include "pico/stdlib.h"
#include "pio_i2c.h"

#include "I2C.h"

class PioI2C : public I2C 
{
    private:
        PIO _pio;
        uint _sm;
        uint _scl;
        uint _sda;
        uint32_t _freq;

    public:
        PioI2C(
            PIO pio,
            uint sm,
            uint scl,
            uint sda,
            uint32_t freq
        );

        ~PioI2C();

        virtual uint init();

        virtual int write_blocking(
            uint8_t addr,
            uint8_t* src,
            uint len,
            bool nostop
        );
};

#endif