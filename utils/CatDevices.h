//
// Created by RHZhang on 2017/9/14.
//
#pragma once

#include "../src/Precompiled.h"
#include "portaudio.h"


struct CatDevices : Singleton<CatDevices>
{
public:
    void CatPortAudioDevice();
};

