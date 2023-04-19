#ifndef _PioI2C_H_
#define _PioI2C_H_

#include "pico/stdlib.h"
#include "Renderer.h"
#include "../models/ChannelModel.h"

class ChannelRenderer : public Renderer 
{
    private:
        ChannelModel* _model;
        OLED* _oled;
        I2C* _i2c;
        bool _dirty;
        void drawChannelOled();

    public:
        ChannelRenderer(
            ChannelModel* model,
            OLED* oled,
            I2C* i2c
        );

        ~ChannelRenderer();

        virtual uint init();

        virtual void render();
};

#endif