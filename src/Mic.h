//
// Created by RHZhang on 2017/9/14.
//

#pragma once

#include <portaudio.h>

struct IExtraCallback
{
    enum cbReturnType {
        paContinue=0,   /**< Signal that the stream should continue invoking the callback and processing audio. */
        paComplete=1,   /**< Signal that the stream should stop invoking the callback and finish once all output samples have played. */
        paAbort=2       /**< Signal that the stream should stop invoking the callback and finish as soon as possible. */
    };

    virtual ~IExtraCallback(){}

    virtual cbReturnType CallbackFunc(const void * inputBuffer,
                     void * outputBuffer,
                     unsigned long framesPerBuffer,
                     const PaStreamCallbackTimeInfo * timeInfo,
                     PaStreamCallbackFlags statusFlags,
                     void * userData
    ) = 0;
};


enum PlanarOrPacked
{
    Planar,
    Packed
};

struct MicParams
{
    int nbChannel;
    int sampleRate;
    int bitDepth;
};



struct Mic
{
public:
    virtual ~Mic(){}

protected:
    Mic(MicParams _MicParams, PlanarOrPacked _PlanarOrPacked, int samplesPerBlock, IExtraCallback *extraCallback)
    :m_MicParams(_MicParams)
            , m_PlanarOrPacked(_PlanarOrPacked)
     ,samplesPerBlock(samplesPerBlock)
    ,extraCallback(extraCallback)
    {}


    virtual bool Start() = 0;
    virtual bool Stop() = 0;


private:
    void onGetPcm(){
        // and call IExtraCallback::CallbackFunc
    }

    int samplesPerBlock;
    IExtraCallback *extraCallback;
    MicParams m_MicParams;
    PlanarOrPacked m_PlanarOrPacked;
};

