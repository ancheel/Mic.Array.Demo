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


#include "Mic.h"

using namespace matrix_hal
struct MicMatrixCreator : Mic
{
    MicMatrixCreator()
    : Mic({kMicrophoneChannels, kSamplingRate, 16}, PlanarOrPacked::Planar, 256, nullptr)
    {

    }

public:
    bool Start() override {

        // ref: mic_energy.cpp

        matrix_hal::WishboneBus bus;
        bus.SpiInit();

        matrix_hal::MicrophoneArray mics;
        mics.Setup(&bus);

        matrix_hal::Everloop everloop;
        everloop.Setup(&bus);

        matrix_hal::EverloopImage image1d;
        int j = 0;
        uint64_t instantE = 0;
        uint64_t avgEnergy = 0;
        std::valarray<uint64_t> localAverage (20);
        localAverage = 0;
        mics.SetGain(8);

        for (int i = 0; i* mics.NumberOfSamples()/kSamplingRate < 10; i++) {
            mics.Read(); /* Reading 8-mics buffer from de FPGA */
            instantE  = 0;
            for (uint32_t s = 0; s < mics.NumberOfSamples(); s++) {
                instantE = instantE + (mics.At(s, 0))*(mics.At(s, 0));
            }

            localAverage[j%20] = instantE;
            avgEnergy = 0;
            for(auto& data : localAverage){
                avgEnergy = (avgEnergy + data);
            }

            avgEnergy = avgEnergy/20;

            for (auto& led : image1d.leds) {
                led.red = avgEnergy>>24;
            }
            everloop.Write(&image1d);

            j++;

        }



        return true;
    }

    bool Stop() override {
        return false;
    }
};
