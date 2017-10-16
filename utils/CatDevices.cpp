//
// Created by RHZhang on 2017/9/14.
//

#include "CatDevices.h"


Logger logger("CatDevices.log");



void CatDevices::CatPortAudioDevice()
{
    logger("Pa_GetVersionText", Pa_GetVersionText());

    if (auto err = Pa_Initialize() != paNoError) {
        throw "Pa_Initialize = err";
    }


    auto numDevices = Pa_GetDeviceCount();
    logger("Numbers of Devices:", numDevices);

    for (auto i = 0; i < numDevices; i++) {
        auto deviceInfo = Pa_GetDeviceInfo(i);
        logger("\n\t\t",
               "No.", i,"\n\t\t",
               "hostApi:", deviceInfo->hostApi,"\n\t\t",
               deviceInfo->name,"\n\t\t",
               "maxInputChannels:", deviceInfo->maxInputChannels,"\n\t\t",
               "maxOutputChannels:", deviceInfo->maxOutputChannels,"\n\t\t"
               );
    }
}


int main(void)
{
    CatDevices::Get()->CatPortAudioDevice();
    return 0;
}

