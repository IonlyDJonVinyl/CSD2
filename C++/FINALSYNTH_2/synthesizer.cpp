#include "synthesizer.h"
#include <cmath>

Synthesizer::Synthesizer(float sampleRate) : sampleRate(sampleRate) {

}

void Synthesizer::setAmplitude(float amp) {
    amplitude = amp;
}

void Synthesizer::setNote(int note) {
    this->note = note;
}

float Synthesizer::getSample() {
    return sample;
}

void Synthesizer::setSampleRate(float sampleRate) {
    this->sampleRate = sampleRate;
}