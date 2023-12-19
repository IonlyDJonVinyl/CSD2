#include "sine.h"
#include "math.h"

Sine::Sine(float frequency, float samplerate):Oscillator(frequency, samplerate){}

void Sine::tick() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  phase += frequency / samplerate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }
  sample = sin(pi * 2 * phase) * amplitude;

}
