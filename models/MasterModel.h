#pragma once

#include <string>
#include "pico/stdlib.h"

struct MasterModel
{
    public:
        bool Dirty = true;

        uint8_t FaderValue = 0;

        bool LayerAButtonPressed = false;
        bool LayerAButtonLit = false;

        bool LayerBButtonPressed = false;
        bool LayerBButtonLit = false;

        std::string IpAddress = std::string("192.168.0.1");
};