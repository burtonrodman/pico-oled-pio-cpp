#pragma once

#include <string>
#include "pico/stdlib.h"

class Renderer
{
    public:
        virtual ~Renderer() {}
        virtual uint init() = 0;
        virtual void render() = 0;

        std::string formatIntToString(char *format, uint8_t value) {
            char buffer[16];
            sprintf(buffer, format, value);
            return std::string(buffer);
        }

        std::string formatIntIntToString(char *format, int value1, int value2) {
            char buffer[16];
            sprintf(buffer, format, value1, value2);
            return std::string(buffer);
        }
};
