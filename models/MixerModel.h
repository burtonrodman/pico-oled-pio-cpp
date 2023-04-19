#ifndef _MixerModel_H_
#define _MixerModel_H_

#include "pico/stdlib.h"
#include "ChannelModel.h"

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