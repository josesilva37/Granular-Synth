#include "SynthEngine.h"
#include <cmath>

void SynthEngine::init(float sr) {
    sampleRate = sr;
}

float SynthEngine::process() {
    float freq = 220.0f;
    float sample = sinf(2.0f * M_PI * freq * phase);
    phase += 1.0f / sampleRate;
    if (phase >= 1.0f) phase -= 1.0f;
    return sample * 0.2f;
}
