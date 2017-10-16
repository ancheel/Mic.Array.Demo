#pragma once

#include "../src/Precompiled.h"

#include "CatDevices.h"
#include <fstream>



struct PcmPlayer
{
public:
    PcmPlayer(const string &filePath, int nbChannel, int sampleRate);
    bool Start();
    bool OnProcess(void *output, int frameCount);
    bool Finished() { return m_isOver; }
    ifstream m_pcmFile;

private:
    int m_nbChannel;
    int m_sampleRate;
    int m_nbSamplePerBlock = (1<<10);
    bool m_isOver = false;
    int m_fileSize = 0;
};



