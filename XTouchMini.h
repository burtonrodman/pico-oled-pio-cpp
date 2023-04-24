#pragma once

#include "I2C.h"
#include "PioI2C.h"
#include "OLED.h"

#include "models/ChannelModel.h"
#include "renderer/Renderer.h"
#include "renderer/ChannelRenderer.h"

OLED* createOledPioI2C(PIO pio, uint program_offset, uint scl, uint sda)
{
    uint sm = pio_claim_unused_sm(pio, false);
    PioI2C pio_i2c(pio, sm, program_offset, scl, sda, 400 * 1000);
    I2C *i2c = &pio_i2c;
    auto oled = new OLED(128, 64, false, i2c);
    return oled;
}

// OLED* createOledHardwareI2C()
// {
//     HardwareI2C hw_u9(7, 6, 400 * 1000, i2c1);
//     I2C* i2c_u9 = &hw_u9;
//     OLED oled_u9(128, 64, false, i2c_u9);

// }

const uint offset0 = pio_add_program(pio0, &i2c_program);
const uint offset1 = pio_add_program(pio1, &i2c_program);

ChannelModel* channels[8] = {
    new ChannelModel { 1, 0 },
    new ChannelModel { 2, 0 },
    new ChannelModel { 3, 0 },
    new ChannelModel { 4, 0 },
    new ChannelModel { 5, 0 },
    new ChannelModel { 6, 0 },
    new ChannelModel { 7, 0 },
    new ChannelModel { 8, 0 }    
};

// OLED* oleds[8] = {
//     createOledPioI2C(pio0, offset0,  3,  2),
//     createOledPioI2C(pio0, offset0, 13, 12),
//     createOledPioI2C(pio0, offset0, 11, 10),
//     createOledPioI2C(pio0, offset0,  9,  8),
//     createOledPioI2C(pio1, offset1, 19, 18),
//     createOledPioI2C(pio1, offset1,  5,  4),
//     createOledPioI2C(pio1, offset1, 15, 14),
//     createOledPioI2C(pio1, offset1, 17, 16),
// };

Renderer* renderers[8] = {
    new ChannelRenderer(channels[0], createOledPioI2C(pio0, offset0,  3,  2)),
    new ChannelRenderer(channels[1], createOledPioI2C(pio0, offset0, 13, 12)),
    new ChannelRenderer(channels[2], createOledPioI2C(pio0, offset0, 11, 10)),
    new ChannelRenderer(channels[3], createOledPioI2C(pio0, offset0,  9,  8)),
    new ChannelRenderer(channels[4], createOledPioI2C(pio1, offset1, 19, 18)),
    new ChannelRenderer(channels[5], createOledPioI2C(pio1, offset1,  5,  4)),
    new ChannelRenderer(channels[6], createOledPioI2C(pio1, offset1, 15, 14)),
    new ChannelRenderer(channels[7], createOledPioI2C(pio1, offset1, 17, 16)),
};