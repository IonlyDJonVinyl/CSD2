#include "tripleosc.h"
#include "sine.h"
#include "saw.h"
#include "square.h"
#include "synthesizer.h"

Oscillator* getOscillator(int type, float frequency, float sampleRate) {
    if (type == 1) {
        return new Sine(frequency, sampleRate);
    } else if (type == 2) {
        return new Saw(frequency, sampleRate);
    } else if (type == 3) {
        return new Square(frequency, sampleRate);
    } else {
        return new Sine(frequency, sampleRate);
    }
}

TripleOsc::TripleOsc(int note, int osc1, float off1, int osc2, float off2, int osc3, float off3, float sampleRate) : Synthesizer(sampleRate) {

    // Create/Allocate new oscillators (IMPORTANT: Uses 'new', so don't forget to delete in destructor)
    oscs[0] = getOscillator(osc1, calcFrequency(note+off1), sampleRate); 
    offsets[0] = off1;
    oscs[1] = getOscillator(osc2, calcFrequency(note+off2), sampleRate);
    offsets[1] = off2;
    oscs[2] = getOscillator(osc3, calcFrequency(note+off3), sampleRate);
    offsets[2] = off3;

    setNote(note);
    //Sine* sine = new Sine(calcFrequency(63), sampleRate);
    //oscs[0] = sine;
}

TripleOsc::~TripleOsc() {
    for (int i = 0; i < 3; i++)
        delete oscs[i];
}

void TripleOsc::setNote(int note) {
    Synthesizer::setNote(note); //Set note of synthesizer
    for (int i = 0; i < 3; i++) {
        oscs[i]->setFrequency(calcFrequency(note+offsets[i])); //Calculate new frequency for each oscillator
    }
}

void TripleOsc::change(int osc1, float off1, int osc2, float off2, int osc3, float off3) {
    auto prev = oscs[0];
    oscs[0] = getOscillator(osc1, calcFrequency(note+off1), sampleRate); 
    offsets[0] = off1;
    delete prev;
    prev = oscs[1];
    oscs[1] = getOscillator(osc2, calcFrequency(note+off2), sampleRate); 
    offsets[1] = off2;
    delete prev;
    prev = oscs[2];
    oscs[2] = getOscillator(osc3, calcFrequency(note+off3), sampleRate); 
    offsets[2] = off3;
    delete prev;
}

void TripleOsc::tick() {
    if (paused) return;
    sample = 0;
    for (int i = 0; i < 3; i++) {
        oscs[i]->tick(); // Tick each oscillator
        sample += oscs[i]->getSample(); // Add them together
    }
    sample *= amplitude*0.33f; //Multiply by amplitude of synthesizer
}