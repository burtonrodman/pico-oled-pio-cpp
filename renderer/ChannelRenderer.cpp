#include <cstdio>
#include "pico/stdlib.h"

#include "../oled/OLED.h"
#include "Renderer.h"
#include "ChannelRenderer.h"
#include "../models/ChannelModel.h"

void ChannelRenderer::drawChannelOled()
{
    _oled->clear();

    char string1[10];
    for (int i = 0; i < 4; i++) {
        sprintf(string1 + i * 2, "%02X", _model->lastMidiMessage[i]);
    }
    _oled->print(0, 0, string1);

    if (_model->dirx == 1 && _model->cx > 96) _model->dirx = -1;
    if (_model->dirx == -1 && _model->cx < 32) _model->dirx = 1;
    if (_model->diry == 1 && _model->cy > 64) _model->diry = -1;
    if (_model->diry == -1 && _model->cy < 32) _model->diry = 1;

    _model->cx += _model->dirx;
    _model->cy += _model->diry;

    _oled->drawCircle(_model->cx, _model->cy, 16);

    char string2[] = "Y";
    _oled->print(_model->cx, _model->cy, string2);
 
    _oled->show();
}

ChannelRenderer::ChannelRenderer(
    ChannelModel* model,
    OLED* oled,
    I2C* i2c
) {
    _model = model;
    _oled = oled;
    _i2c = i2c;
}

ChannelRenderer::~ChannelRenderer() { }

uint ChannelRenderer::init() {
    return 0;
}

void ChannelRenderer::render() {
    // if (_dirty == true) {
        drawChannelOled();
    //     _dirty = false;
    // }
}