#ifndef _ChannelModel_H_
#define _ChannelModel_H_

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
        uint8_t EncoderValue = 0;
        EncoderTypes EncoderType = Single;
        bool EncoderPressed = false;

        bool Button1Pressed = false;
        bool Button1Lit = false;

        bool Button2Pressed = false;
        bool Button2Lit = false;

        uint8_t cx = 32;
        uint8_t cy = 32;
        int dirx = 1;
        int diry = 1;

        uint8_t lastMidiMessage[4];
};

#endif