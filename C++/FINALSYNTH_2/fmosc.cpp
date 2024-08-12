#include "fmosc.h"
#include "math.h"

Fmosc::Fmosc(Oscillator* oscillator, Oscillator* modulator, float samplerate):
        Synthesizer(samplerate), oscillator(oscillator), modulator(modulator) {
}

void Fmosc::tick() {
  float originalFrequency = (oscillator->getFrequency()-modOffset) / (modulator->getSample()+1);

  modulator->tick();

  oscillator->setFrequency( originalFrequency * (modulator->getSample()+1) + modOffset );
  this->setFrequency(oscillator->getFrequency());

  oscillator->tick();
  this->sample = oscillator->getSample();
}

void Fmosc::setNote(int note) {
    Synthesizer::setNote(note); //Set note of synthesizer
        oscillator->setFrequency(calcFrequency(note+offsets[i])); //Calculate new frequency for each oscillator
}