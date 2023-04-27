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
};
