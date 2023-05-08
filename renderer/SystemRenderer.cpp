#include <cstdio>
#include <string>
#include "pico/stdlib.h"

#include "../oled/OLED.h"
#include "../oled/font/Cousine_Regular_12.h"

#include "Renderer.h"
#include "SystemRenderer.h"
#include "../models/SystemModel.h"

void SystemRenderer::drawSystemOled()
{
    _oled->clear();
    _oled->setFont(&Cousine_Regular_12);

    _oled->print(0, 0, _model->IpAddress);

    if (_model->LayerAButtonPressed) {
        std::string a = std::string("A");
        _oled->print(32, 40, a);
    }

    if (_model->LayerBButtonPressed) {
        std::string b = std::string("B");
        _oled->print(48, 40, b);
    }

    _oled->show();
}

SystemRenderer::SystemRenderer(
    SystemModel* model,
    OLED* oled
) {
    _model = model;
    _oled = oled;
}

SystemRenderer::~SystemRenderer() { }

uint SystemRenderer::init() {
    return 0;
}

void SystemRenderer::render() {
    if (_model->Dirty) {
        drawSystemOled();
        _model->Dirty = false;
    }
}