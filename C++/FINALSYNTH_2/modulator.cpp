#include "modulator.h"

Modulator::Modulator(Oscillator* mod, Oscillator* osc, float maxDifference): mod(mod), osc(osc), maxDifference(maxDifference), Oscillator(osc->getFrequency(), osc->getSampleRate()){
    osc->setFrequency(osc->getFrequency()*std::pow(2, (mod->getSample()*maxDifference)/12));
}

void Modulator::tick() {
    float currFrequency = osc->getFrequency();
    float baseFrequency = currFrequency/std::pow(2, (mod->getSample()*maxDifference)/12); //reverse of modulator
    mod->tick();
    osc->setFrequency(baseFrequency*std::pow(2, (mod->getSample()*maxDifference)/12));
    this->setFrequency(osc->getFrequency());
    osc->tick();
    this->sample = osc->getSample();
}

void Modulator::setOscillator(Oscillator* oscillator) {
    this->osc = oscillator;
    osc->setFrequency(osc->getFrequency()*std::pow(2, (maxDifference*mod->getSample()/12)));
}

Oscillator* Modulator::getOscillator() {
    return this->osc;
}