#include <cstdio>
#include <string>
#include "pico/stdlib.h"

#include "I2C.h"
#include "PioI2C.h"
#include "pio_i2c.h"
// #include "i2c.pio.h"

#include "../oled/OLED.h"
#include "../oled/font/Cherry_Cream_Soda_Regular_16.h"

#include "Renderer.h"
#include "ChannelRenderer.h"
#include "../models/ChannelModel.h"

void ChannelRenderer::drawChannelOled()
{
    _oled->clear();

    // char string1[10];
    // for (int i = 0; i < 4; i++) {
    //     sprintf(string1 + i * 2, "%02X", _model->lastMidiMessage[i]);
    // }
    std::string message = "message";
    _oled->print(0, 0, message);

    // if (_model->dirx == 1 && _model->cx > 96) _model->dirx = -1;
    // if (_model->dirx == -1 && _model->cx < 32) _model->dirx = 1;
    // if (_model->diry == 1 && _model->cy > 64) _model->diry = -1;
    // if (_model->diry == -1 && _model->cy < 32) _model->diry = 1;

    // _model->cx += _model->dirx;
    // _model->cy += _model->diry;

    // _oled->drawCircle(_model->cx, _model->cy, 16);

    char buf[8];
    sprintf(buf, "%d", _model->EncoderValue);
    std::string string2 = std::string(buf);
    _oled->print(_model->cx, _model->cy, string2);
 
    _oled->show();
}

ChannelRenderer::ChannelRenderer(
    ChannelModel* model,
    OLED* oled
) {
    _model = model;
    _oled = oled;
}

ChannelRenderer::~ChannelRenderer() { }

uint ChannelRenderer::init() {
    return 0;
}

void ChannelRenderer::render() {
    if (_model->Dirty) {
        drawChannelOled();
        _model->Dirty = false;
    }
}