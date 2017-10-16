#include "PcmPlayer.h"

Logger logger("PcmPlayer.log");

extern "C"
{
int s_thePaStreamCallback(
        const void *input, void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo *timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData);
}


PcmPlayer::PcmPlayer(const string &filePath, int nbChannel, int sampleRate)
    : m_pcmFile(filePath, ios::binary)
    , m_nbChannel(nbChannel)
    , m_sampleRate(sampleRate)
{
    logger("Pa_GetVersionText", Pa_GetVersionText());

    if (auto err = Pa_Initialize() != paNoError) {
        throw "Pa_Initialize = err";
    }

    logger("File Path:", filePath);
    logger("Numbers of Channel:", nbChannel);
    logger("Sample Rate:", sampleRate);


    // Get File Size
    {
        m_pcmFile.seekg(ios::end);
        m_fileSize = m_pcmFile.tellg();
        m_pcmFile.seekg(ios::beg);
    }
}

bool PcmPlayer::OnProcess(void *output, int frameCount)
{
    try{
        const int sz = frameCount*sizeof(int16_t)*m_nbChannel;
        if (!m_pcmFile.read((char*)output, sz)){
            m_isOver = true;
            logger("End of file");
            return false;
        }
    }
    catch(exception &e){
        logger(e.what());
        m_isOver = true;
        return false;
    }

    return true;
}



bool PcmPlayer::Start()
{
    // Use the default output device
    PaStream *stream = nullptr;

    try {
        PaStreamParameters outputParameters;

        outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
        outputParameters.channelCount = m_nbChannel;
        outputParameters.sampleFormat = paInt16;
        outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = nullptr;
        /* -- setup stream -- */
        auto err = Pa_OpenStream(
                    &stream,
                    nullptr,
                    &outputParameters,
                    m_sampleRate,
                    m_nbSamplePerBlock,
                    paClipOff,      /* we won't output out of range samples so don't bother clipping them */
                    s_thePaStreamCallback,
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


    return paNoError == Pa_StartStream(stream);
}



int s_thePaStreamCallback(
        const void *input, void *output,
        unsigned long frameCount,
        const PaStreamCallbackTimeInfo *timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData)
{
    auto thePcmPlayer = (PcmPlayer*)(userData);

    if (!thePcmPlayer->OnProcess(output,frameCount)){
        return paComplete;
    }

    return paContinue;
}



// tips: ffmpeg -i *.wav -f s16le -acodec pcm_s16le *.pcm
int main(int argc, char *argv[])
{
    if (argc!=4){
        cout << "PcmPlayer: playing s16le raw file" << endl;
        cout << "usage: ./PcmPlayer thePcmFilename channels sampleRate" << endl;
        return -1;
    }

    // Open File
    try{
        string fileName = argv[1];
        int nbChannel = stoi(argv[2]);
        int sampleRate = stoi(argv[3]);
        PcmPlayer player(fileName, nbChannel, sampleRate);
        player.Start();

        for (;;)
        {
            this_thread::sleep_for(1s);
            if (player.Finished()){
                break;
            }
        }
    }
    catch(exception &e){
        logger(e.what());
        return -1;
    }



    logger("Bye");
    return 0;
}
