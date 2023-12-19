#ifndef _SYNTHESIZER_H_
#define _SYNTHESIZER_H_

#include <math.h>

const static float a4Frequency = 440.0f;
const static float semitoneRatio = pow(2.0f, 1.0f / 12.0f); // Ratio of frequencies between semitones


class Synthesizer {

public:
    Synthesizer(float sampleRate);

    void setAmplitude(float amp);
    virtual void setNote(int note);
    void setSampleRate(float sr);
    float getSample();

    float calcFrequency(float note) {
        float distanceFromA4 = note - 69;
        float frequency = a4Frequency * pow(semitoneRatio, distanceFromA4);
        return frequency;
    }

    virtual void tick() = 0;
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