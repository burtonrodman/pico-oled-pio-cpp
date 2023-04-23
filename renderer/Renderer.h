#pragma once

#include "pico/stdlib.h"

class Renderer
{
    public:
        virtual ~Renderer() {}
        virtual uint init() = 0;
        virtual void render() = 0;
};
