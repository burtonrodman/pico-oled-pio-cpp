#pragma once

#include <string>
#include "pico/stdlib.h"

struct SystemModel
{
    public:
        bool Dirty = true;

        bool LayerAButtonPressed = false;
        bool LayerAButtonLit = false;

        bool LayerBButtonPressed = false;
        bool LayerBButtonLit = false;

        std::string IpAddress = std::string("192.168.0.1");
        
        bool ProcessMidiMessage(uint8_t *message, uint8_t len) {
            auto a = message[0];
            auto b = message[1];
            auto c = message[2];

            if (a == 0x90 && b == 0x54) {
                LayerAButtonPressed = (c == 0x7f);
            }
            if (a == 0x90 && b == 0x55) {
                LayerBButtonPressed = (c == 0x7f);
            }
            
            Dirty = true;
            return true;
        }

};