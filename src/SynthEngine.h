#pragma once

class SynthEngine {
public:
    void init(float sampleRate);
    float process();
private:
    float phase = 0.0f;
    float sampleRate = 48000.0f;
};
