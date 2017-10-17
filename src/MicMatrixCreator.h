//
// Created by RHZhang on 2017/9/14.
//

#pragma once

#include <matrix_hal/microphone_array.h>
#include <matrix_hal/everloop_image.h>
#include <matrix_hal/everloop.h>
#include <matrix_hal/microphone_array.h>
#include <matrix_hal/wishbone_bus.h>

#include <cstdint>
#include <valarray>
#include <portaudio.h>

#include "Mic.h"

using namespace matrix_hal
struct MicMatrixCreator : Mic
{
public:
    MicMatrixCreator();
    virtual bool Start() override;
    virtual bool Stop() override;
private:
    bool InitPA();
    // Use the default output device
    PaStream *m_stream = nullptr;
    int m_sampleRate;
    int m_nbSamplePerBlock;

};
