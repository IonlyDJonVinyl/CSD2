#include "fmosc.h"
#include "math.h"

Fmosc::Fmosc(Oscillator* oscillator, Oscillator* modulator, float samplerate):
        Oscillator(oscillator->getFrequency(), samplerate), oscillator(oscillator), modulator(modulator) {
}

void Fmosc::tick() {
  float originalFrequency = (oscillator->getFrequency()-modOffset) / (modulator->getSample()+1);

  modulator->tick();

  oscillator->setFrequency( originalFrequency * (modulator->getSample()+1) + modOffset );
  this->setFrequency(oscillator->getFrequency());

  oscillator->tick();
  this->sample = oscillator->getSample();
}
