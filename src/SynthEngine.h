#pragma once

class SynthEngine {
public:
    void init(float sampleRate);
    float process();
private:
    float phase = 0.0f;
    float sampleRate = 44100.0f;
};
