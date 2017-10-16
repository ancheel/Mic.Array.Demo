#pragma once

#include "../src/Precompiled.h"

#include "CatDevices.h"
#include <fstream>
#include <vector>


struct FileReader
{
public:
    virtual ~FileReader() { }
    virtual bool Load(const string &filePath) = 0;
    virtual bool Read(char* buffer, size_t size) = 0;
    virtual size_t GetSize() = 0;
};




struct SimplestFileReader : FileReader
{
    // FileReader interface
public:
    bool Load(const string &filePath);
    bool Read(char *buffer, size_t size);
    size_t GetSize(){return m_fileSize;}

private:
    ifstream m_pcmFile;
    int m_fileSize = 0;
};



struct FileReader_ReadOnce : FileReader
{
    // FileReader interface
public:
    bool Load(const string &filePath);
    bool Read(char *buffer, size_t size);
    size_t GetSize();

private:
    int m_fileSize = 0;
    vector<char> m_buffer;
    int m_currPos = 0;
};





struct PcmPlayer
{
public:
    PcmPlayer(const string &filePath, int nbChannel, int sampleRate);
    bool Start();
    bool OnProcess(void *output, int frameCount);
    bool Finished() { return m_isOver; }

private:
    int m_nbChannel;
    int m_sampleRate;
    int m_nbSamplePerBlock = (1<<10);
    bool m_isOver = false;
    // SimplestFileReader m_reader;
    FileReader_ReadOnce m_reader;
};



