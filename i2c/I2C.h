#ifndef _I2C_H_
#define _I2C_H_

#include "pico/stdlib.h"

class I2C
{
    public:
        virtual ~I2C() {}
        virtual uint init() = 0;
        virtual int write_blocking(
            uint8_t addr,
            uint8_t* src,
            uint len,
            bool nostop
        ) = 0;
};

#endif