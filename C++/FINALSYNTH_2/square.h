#ifndef _SQUARE_H_
#define _SQUARE_H_
#include <iostream>
#include <cmath>
#include "oscillator.h"

class Square:public Oscillator
{
public:
   void tick();
   Square(float frequency, float samplerate = 44100);
};

#endif