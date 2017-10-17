//
// Created by RHZhang on 2017/9/14.
//

#include "MicMatrixCreator.h"

extern Logger logger;

MicMatrixCreator::MicMatrixCreator()
    : Mic({kMicrophoneChannels, kSamplingRate, 16}, PlanarOrPacked::Planar, 256, nullptr)
{

}

bool MicMatrixCreator::Start()
{
    // ref: mic_energy.cpp

    matrix_hal::WishboneBus bus;
    bus.SpiInit();

    matrix_hal::MicrophoneArray mics;
    m_nbSamplePerBlock=mics.NumberOfSamples();
    mics.Setup(&bus);
    mics.SetGain(8); // ?


    if (!InitPA()){
        return false;
    }

    for (;;){
        mics.Read(); /* Reading 8-mics buffer from de FPGA */



        auto err = Pa_WriteStream( m_stream, &(mics.Beam(0)), m_nbSamplePerBlock );
        if( err ) {
            logger("Pa_WriteStream error:", err);
            break;
        }

    }



    return true;
}

bool MicMatrixCreator::Stop() {
    return false;
}

bool MicMatrixCreator::InitPA()
{

    try {
        PaStreamParameters outputParameters;

        outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
        outputParameters.channelCount = 1;
        outputParameters.sampleFormat = paInt16;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = nullptr;
        /* -- setup stream -- */
        auto err = Pa_OpenStream(
                    &m_stream,
                    nullptr,
                    &outputParameters,
                    kSamplingRate,
                    m_nbSamplePerBlock,
                    paClipOff,      /* we won't output out of range samples so don't bother clipping them */
                    nullptr,
                    this
                    ); /* no callback, so no callback userData */

        logger("Pa_OpenStream OK!");
        if (err) {
            logger("Pa_OpenStream failed:", err);
            throw;
        }
    }
    catch (exception &e) {
        logger(e.what());
    }


    return paNoError == Pa_StartStream(m_stream);
}
