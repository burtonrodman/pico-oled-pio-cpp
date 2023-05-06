#pragma once

#include "pico/stdlib.h"

enum EncoderTypes
{
    Single,
    Pan,
    Fan,
    Spread,
    Trim
};

struct ChannelModel
{
    public:
        uint8_t ChannelNumber = 0;
        uint8_t EncoderValue = 0x7f;
        EncoderTypes EncoderType = Single;
        bool EncoderPressed = false;

        bool Button1Pressed = false;
        bool Button1Lit = false;

        bool Button2Pressed = false;
        bool Button2Lit = false;

        uint8_t lastMidiMessage[4];
        bool Dirty = true;

        bool ProcessMidiMessage(uint8_t *message, uint8_t len) {
            auto a = message[0];
            auto b = message[1];
            auto c = message[2];

            if (a == 0xb0) {
                if (c > 0x00 && c < 0x08) {
                    if (EncoderValue > 0xff - 7)
                        EncoderValue = 0xff;
                    else
                        EncoderValue += c;
                }
                if (c > 0x40 && c < 0x48) {
                    if (EncoderValue < (c - 0x40)) {
                        EncoderValue = 0;
                    } else {
                        EncoderValue -= (c - 0x40);
                    }
                }
            }
            if (a == 0x90 && b >= 0x20 && b <= 0x27) {
                EncoderPressed = (c == 0x7f);
            }
            if (a == 0x90 && (b == 0x59 || b == 0x5a || (b >= 0x28 && b <= 0x2d)))
            {
                Button1Pressed = (c == 0x7f);
            }
            if (a == 0x90 && (b == 0x56 || b == 0x57 || b == 0x58 || (b >= 0x5b && b <= 0x5f)))
            {
                Button2Pressed = (c == 0x7f);
            }
            
            Dirty = true;
            return true;
        }
};
