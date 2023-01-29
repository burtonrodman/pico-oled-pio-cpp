#ifndef _HardwareI2C_H_
#define _HardwareI2C_H_

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#include "I2C.h"

class HardwareI2C : public I2C 
{
    private:
        uint8_t _scl;
        uint8_t _sda;
        uint32_t _freq;
        i2c_inst_t* _i2c;

    public:
        HardwareI2C(
            uint8_t scl,
            uint8_t sda,
            uint32_t freq,
            i2c_inst_t* i2c
        );

        ~HardwareI2C();

        virtual uint init();

        virtual int write_blocking(
            uint8_t addr,
            const uint8_t* src,
            size_t len,
            bool nostop
        );
};

#endif