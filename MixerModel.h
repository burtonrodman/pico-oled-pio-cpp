#ifndef _MixerModel_H_
#define _MixerModel_H_

#include "pico/stdlib.h"

enum EncoderTypes
{
    Single,
    Pan,
    Fan,
    Spread,
    Trim
};

struct Channel
{
    public:
        uint8_t EncoderValue = 0;
        EncoderTypes EncoderType = Single;
        bool EncoderPressed = false;

        bool Button1Pressed = false;
        bool Button1Lit = false;

        bool Button2Pressed = false;
        bool Button2Lit = false;
};

struct MasterSection
{
    public:
        uint8_t FaderValue = 0;

        bool LayerAButtonPressed = false;
        bool LayerAButtonLit = false;

        bool LayerBButtonPressed = false;
        bool LayerBButtonLit = false;
};

struct MixerModel
{
    public:
        MasterSection* Master;        
        Channel* Channels[8]; 
};

#endif