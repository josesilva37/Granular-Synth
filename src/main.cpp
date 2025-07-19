#include <iostream>
#include <csignal>
#include <cmath>
#include <RtAudio.h>
#include "SynthEngine.h"
#include <chrono>
#include <thread>

bool keepRunning = true;

void signalHandler(int)
{
    keepRunning = false;
}

int audioCallback(void *outputBuffer, void *_inputBuffer, unsigned int nFrames,
                  double _streamTime, RtAudioStreamStatus status, void *userData)
{
    if (status)
        std::cerr << "Stream underflow detected!" << std::endl;

    float *buffer = static_cast<float *>(outputBuffer);
    SynthEngine *synth = static_cast<SynthEngine *>(userData);

    for (unsigned int i = 0; i < nFrames; ++i)
    {
        float sample = synth->process(); // Single float mono output
        buffer[i] = sample;
    }

    return 0;
}

int main()
{
    std::signal(SIGINT, signalHandler);

    RtAudio audio;

    if (audio.getDeviceCount() < 1)
    {
        std::cerr << "No audio devices found" << std::endl;
        return 1;
    }

    unsigned int sampleRate = 48000;
    unsigned int bufferFrames = 256;
    SynthEngine synth;
    synth.init(sampleRate);

    RtAudio::StreamParameters outParams;
    outParams.deviceId = audio.getDefaultOutputDevice();
    std::cout << "Audio Device: " << audio.getDefaultOutputDevice();
    outParams.nChannels = 1; // Mono output
    outParams.firstChannel = 0;
    try
    {

        audio.openStream(&outParams, nullptr, RTAUDIO_FLOAT32, sampleRate, &bufferFrames, &audioCallback, &synth);

        audio.startStream();

        std::cout << "Audio Stream Started, Press Ctrl+C to quite\n";

        while (keepRunning)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        audio.stopStream();
    }
    catch (RtAudioError &error)
    {  
        error.printMessage();
        return 1;
    }

    if (audio.isStreamOpen())
        audio.closeStream();
    return 0;
}