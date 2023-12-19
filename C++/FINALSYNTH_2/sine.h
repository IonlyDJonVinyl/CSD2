#ifndef _SINE_H_
#define _SINE_H_
#include <iostream>
#include <cmath>
#include "oscillator.h"

class Sine:public Oscillator
{
public:
   void tick();
   Sine(float frequency, float samplerate = 44100);
};

#endif