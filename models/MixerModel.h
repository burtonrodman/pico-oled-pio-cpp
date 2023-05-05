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
    private:
    
        uint8_t GetMessageChannelNumber(uint8_t *message, uint8_t len) {
            if (
                (message[0] == 0xb0 && message[1] == 0x10) ||
                (message[0] == 0x90 && message[1] == 0x20) ||
                (message[0] == 0x90 && message[1] == 0x59) ||
                (message[0] == 0x90 && message[1] == 0x57)
            ) {
                return 1;
            }

            if (
                (message[0] == 0xb0 && message[1] == 0x11) ||
                (message[0] == 0x90 && message[1] == 0x21) ||
                (message[0] == 0x90 && message[1] == 0x5A) ||
                (message[0] == 0x90 && message[1] == 0x58)
            ) {
                return 2;
            }

            if (
                (message[0] == 0xb0 && message[1] == 0x12) ||
                (message[0] == 0x90 && message[1] == 0x22) ||
                (message[0] == 0x90 && message[1] == 0x28) ||
                (message[0] == 0x90 && message[1] == 0x5b)
            ) {
                return 3;
            }

            if (
                (message[0] == 0xb0 && message[1] == 0x13) ||
                (message[0] == 0x90 && message[1] == 0x23) ||
                (message[0] == 0x90 && message[1] == 0x29) ||
                (message[0] == 0x90 && message[1] == 0x5c)
            ) {
                return 4;
            }

            if (
                (message[0] == 0xb0 && message[1] == 0x14) ||
                (message[0] == 0x90 && message[1] == 0x24) ||
                (message[0] == 0x90 && message[1] == 0x2a) ||
                (message[0] == 0x90 && message[1] == 0x56)
            ) {
                return 5;
            }

            if (
                (message[0] == 0xb0 && message[1] == 0x15) ||
                (message[0] == 0x90 && message[1] == 0x25) ||
                (message[0] == 0x90 && message[1] == 0x2b) ||
                (message[0] == 0x90 && message[1] == 0x5d)
            ) {
                return 6;
            }

            if (
                (message[0] == 0xb0 && message[1] == 0x16) ||
                (message[0] == 0x90 && message[1] == 0x26) ||
                (message[0] == 0x90 && message[1] == 0x2c) ||
                (message[0] == 0x90 && message[1] == 0x5e)
            ) {
                return 7;
            }

            if (
                (message[0] == 0xb0 && message[1] == 0x17) ||
                (message[0] == 0x90 && message[1] == 0x27) ||
                (message[0] == 0x90 && message[1] == 0x2d) ||
                (message[0] == 0x90 && message[1] == 0x5f)
            ) {
                return 8;
            }

            return 0;
        }

    public:
        MasterSection* Master;        
        std::vector<ChannelModel*> Channels;

        void DispatchMidiMessage(uint8_t *message, uint8_t len) {
            auto channel = GetMessageChannelNumber(message, len);
            if (channel > 0) {
                Channels[channel - 1]->ProcessMidiMessage(message, len);
            }
        }
};
