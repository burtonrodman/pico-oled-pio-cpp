#include <cstdio>
#include <string>
#include "pico/stdlib.h"

#include "../oled/OLED.h"
#include "../oled/font/Cherry_Cream_Soda_Regular_16.h"

#include "Renderer.h"
#include "MasterRenderer.h"
#include "../models/MasterModel.h"

void MasterRenderer::drawMasterOled()
{
    _oled->clear();

    _oled->print(0, 0, _model->IpAddress);
 
    _oled->show();
}

MasterRenderer::MasterRenderer(
    MasterModel* model,
    OLED* oled
) {
    _model = model;
    _oled = oled;
}

MasterRenderer::~MasterRenderer() { }

uint MasterRenderer::init() {
    return 0;
}

void MasterRenderer::render() {
    if (_model->Dirty) {
        drawMasterOled();
        _model->Dirty = false;
    }
}