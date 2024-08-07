#include "synthesizer.h"
#include <cmath>

Synthesizer::Synthesizer(float sampleRate) : Oscillator(calcFrequency(this->note), sampleRate) {

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

void Synthesizer::setFrequency(float frequency) {
    this->frequency = frequency;
    this->setNote(this->calcNote(frequency));
}

float Synthesizer::getFrequency(){
    return this->calcFrequency(note);
}

void Synthesizer::setSampleRate(float sampleRate) {
    this->sampleRate = sampleRate;
}