#ifndef _SYNTHESIZER_H_
#define _SYNTHESIZER_H_

#include <math.h>
#include "oscillator.h"

const static float a4Frequency = 440.0f;
const static float semitoneRatio = pow(2.0f, 1.0f / 12.0f); // Ratio of frequencies between semitones


class Synthesizer : public Oscillator {

public:
    Synthesizer(float sampleRate);

    void setAmplitude(float amp);
    virtual void setNote(int note);
    void setSampleRate(float sr);
    float getSample();


    void setFrequency(float frequency);
    float getFrequency();

    float calcFrequency(float note) {
        float distanceFromA4 = note - 69;
        float frequency = a4Frequency * pow(semitoneRatio, distanceFromA4);
        return frequency;
    }
    float calcNote(float frequency) {
        float distanceFromA4 = std::pow((frequency / a4Frequency), 1.0f/distanceFromA4);
        return distanceFromA4 + 69;
    }

    void pause() { paused = true; }
    void resume() { paused = false; }
protected:
    int note = 0;
    float amplitude = 1;
    float sample = 0;
    float sampleRate;
    bool paused = false;
};

#endif