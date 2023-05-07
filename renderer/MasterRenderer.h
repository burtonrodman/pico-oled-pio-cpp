#pragma once

#include "pico/stdlib.h"
#include "Renderer.h"
#include "../models/MasterModel.h"

class MasterRenderer : public Renderer 
{
    private:
        MasterModel* _model;
        OLED* _oled;
        void drawMasterOled();

    public:
        MasterRenderer(
            MasterModel* model,
            OLED* oled
        );

        ~MasterRenderer();

        virtual uint init();

        virtual void render();
};
