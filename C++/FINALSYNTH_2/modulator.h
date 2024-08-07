#ifndef _MODULATOR_H_
#define _MODULATOR_H_

#include <iostream>
#include <cmath>
#include "oscillator.h"
class Modulator : public Oscillator {
public:
  //Constructor and destructor
  Modulator(Oscillator* mod, Oscillator* osc, float maxDifference);
  void tick();

  void setModFrequency(float mod);

  void setOscillator(Oscillator* oscillator);
  Oscillator* getOscillator();

protected:
  float maxDifference;
  Oscillator* osc;
  Oscillator* mod;
};

#endif