#pragma once

#include "pico/stdlib.h"
#include "Renderer.h"
#include "../models/SystemModel.h"

class SystemRenderer : public Renderer 
{
    private:
        SystemModel* _model;
        OLED* _oled;
        void drawSystemOled();

    public:
        SystemRenderer(
            SystemModel* model,
            OLED* oled
        );

        ~SystemRenderer();

        virtual uint init();

        virtual void render();
};
