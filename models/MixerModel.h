#pragma once

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
        std::vector<ChannelModel*> Channels; 
};
