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
        bool Dirty = true;

        bool ProcessMidiMessage(uint8_t *message, uint8_t len) {
            // channel 1 - B010 - KNOB TURN; 9020 - KNOB PUSH; 9059 - BUTTON1; 9057 - BUTTON2

            if (GetMessageChannelNumber(message, len) == ChannelNumber) {
                for (int i = 0; i < len; i++) {
                    lastMidiMessage[i] = message[i];
                }
                Dirty = true;
                return true;
            }

            return false;
        }

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

            return 3;
        }
};
