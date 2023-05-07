#pragma once

#include <string>
#include "pico/stdlib.h"

struct MasterModel
{
    public:
        bool Dirty = true;

        uint8_t FaderValue = 0;
    
        bool ProcessMidiMessage(uint8_t *message, uint8_t len) {
            auto a = message[0];
            auto c = message[2];

            if (a == 0xe8) {
                FaderValue = c;
            }
            
            Dirty = true;
            return true;
        }

};