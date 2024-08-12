#ifndef _FMOSC_H_
#define _FMOSC_H_
#include <iostream>
#include <cmath>
#include "oscillator.h"

class Fmosc:public Synthesizer
{
public:
   Fmosc(Oscillator* oscillator, Oscillator* modulator, float samplerate = 44100);
   void tick();
   void setNote(int note);


private:
   Oscillator* modulator;
   Oscillator* oscillator;
   float modOffset = 0;

};

#endif