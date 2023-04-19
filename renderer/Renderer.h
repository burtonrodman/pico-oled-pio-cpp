#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "pico/stdlib.h"

class Renderer
{
    public:
        virtual ~Renderer() {}
        virtual uint init() = 0;
        virtual void render() = 0;
};

#endif