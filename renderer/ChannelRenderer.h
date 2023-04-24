#pragma once

#include "pico/stdlib.h"
#include "Renderer.h"
#include "../models/ChannelModel.h"

class ChannelRenderer : public Renderer 
{
    private:
        ChannelModel* _model;
        OLED* _oled;
        bool _dirty;
        void drawChannelOled();

    public:
        ChannelRenderer(
            ChannelModel* model,
            OLED* oled
        );

        ~ChannelRenderer();

        virtual uint init();

        virtual void render();
};
