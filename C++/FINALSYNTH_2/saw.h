#ifndef _SAW_H_
#define _SAW_H_
#include <iostream>
#include <cmath>
#include "oscillator.h"

class Saw:public Oscillator
{
public:
   Saw(float frequency, float samplerate = 44100);

   void tick();
};

#endif
