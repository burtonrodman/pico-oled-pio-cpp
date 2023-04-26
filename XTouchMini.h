#pragma once

#include <vector>
#include "I2C.h"
#include "PioI2C.h"
#include "OLED.h"

#include "models/ChannelModel.h"
#include "renderer/Renderer.h"
#include "renderer/ChannelRenderer.h"

OLED* createOledPioI2C(PIO pio, uint program_offset, uint scl, uint sda)
{
    uint sm = pio_claim_unused_sm(pio, false);
    auto pio_i2c = new PioI2C(pio, sm, program_offset, scl, sda, 400 * 1000);
    I2C* i2c = pio_i2c;
    auto oled = new OLED(128, 64, false, i2c);
    return oled;
}

// OLED* createOledHardwareI2C()
// {
//     HardwareI2C hw_u9(7, 6, 400 * 1000, i2c1);
//     I2C* i2c_u9 = &hw_u9;
//     OLED oled_u9(128, 64, false, i2c_u9);

// }

std::vector<ChannelModel*> createChannelModels()
{
    std::vector<ChannelModel*> channels = {
        new ChannelModel{1, 0},
        new ChannelModel{2, 0},
        new ChannelModel{3, 0},
        new ChannelModel{4, 0},
        new ChannelModel{5, 0},
        new ChannelModel{6, 0},
        new ChannelModel{7, 0},
        new ChannelModel{8, 0}
    };
    return channels;
}

std::vector<Renderer*> createRenderers(
    std::vector<ChannelModel *> channels,
    const uint offset0,
    const uint offset1)
{
    std::vector<Renderer*> renderers = {
        new ChannelRenderer(channels[0], createOledPioI2C(pio0, offset0,  3,  2)),
        new ChannelRenderer(channels[1], createOledPioI2C(pio0, offset0, 13, 12)),
        new ChannelRenderer(channels[2], createOledPioI2C(pio0, offset0, 11, 10)),
        new ChannelRenderer(channels[3], createOledPioI2C(pio0, offset0,  9,  8)),
        new ChannelRenderer(channels[4], createOledPioI2C(pio1, offset1,  7,  6)),
        new ChannelRenderer(channels[5], createOledPioI2C(pio1, offset1,  5,  4)),
        new ChannelRenderer(channels[6], createOledPioI2C(pio1, offset1, 15, 14)),
        new ChannelRenderer(channels[7], createOledPioI2C(pio1, offset1, 17, 16))
    };
    return renderers;
}
