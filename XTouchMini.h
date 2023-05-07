#pragma once

#include <vector>

#include "hardware/i2c.h"

#include "I2C.h"
#include "PioI2C.h"
#include "HardwareI2C.h"
#include "OLED.h"

#include "models/MixerModel.h"
#include "models/ChannelModel.h"
#include "renderer/Renderer.h"
#include "renderer/ChannelRenderer.h"
#include "renderer/MasterRenderer.h"

OLED* createOledPioI2C(PIO pio, uint program_offset, uint scl, uint sda)
{
    uint sm = pio_claim_unused_sm(pio, false);
    auto pio_i2c = new PioI2C(pio, sm, program_offset, scl, sda, 400 * 1000);
    I2C* i2c = pio_i2c;
    auto oled = new OLED(128, 64, false, i2c);
    return oled;
}

OLED* createOledHardwareI2C(uint scl, uint sda, i2c_inst_t* i2c_inst)
{
    auto hw_i2c = new HardwareI2C(scl, sda, 400 * 1000, i2c_inst);
    I2C* i2c = hw_i2c;
    auto oled = new OLED(128, 64, false, i2c);
    return oled;
}

std::vector<ChannelModel*> createChannelModels()
{
    std::vector<ChannelModel*> channels = {
        new ChannelModel{1},
        new ChannelModel{2},
        new ChannelModel{3},
        new ChannelModel{4},
        new ChannelModel{5},
        new ChannelModel{6},
        new ChannelModel{7},
        new ChannelModel{8}
    };
    return channels;
}

MixerModel* createMixerModel() {
    MixerModel* mixer = new MixerModel();
    mixer->Master = new MasterModel();
    mixer->Channels = createChannelModels();
    return mixer;
}

std::vector<Renderer*> createRenderers(
    MixerModel* mixer,
    const uint offset0,
    const uint offset1)
{
    std::vector<Renderer*> renderers;
    renderers.push_back(new ChannelRenderer(mixer->Channels[0], createOledPioI2C(pio0, offset0,  3,  2)));
    renderers.push_back(new ChannelRenderer(mixer->Channels[1], createOledPioI2C(pio0, offset0, 13, 12)));
    renderers.push_back(new ChannelRenderer(mixer->Channels[2], createOledPioI2C(pio0, offset0, 11, 10)));
    renderers.push_back(new ChannelRenderer(mixer->Channels[3], createOledPioI2C(pio0, offset0,  9,  8)));
    renderers.push_back(new ChannelRenderer(mixer->Channels[4], createOledPioI2C(pio1, offset1,  7,  6)));
    renderers.push_back(new ChannelRenderer(mixer->Channels[5], createOledPioI2C(pio1, offset1,  5,  4)));
    renderers.push_back(new ChannelRenderer(mixer->Channels[6], createOledPioI2C(pio1, offset1, 15, 14)));
    renderers.push_back(new ChannelRenderer(mixer->Channels[7], createOledPioI2C(pio1, offset1, 17, 16)));
    renderers.push_back(new MasterRenderer(mixer->Master, createOledHardwareI2C(21, 20, i2c0)));
        // new MasterRenderer(createOledHardwareI2C(19, 18))

    return renderers;
}
