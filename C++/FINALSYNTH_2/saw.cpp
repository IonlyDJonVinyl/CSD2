#include "saw.h"
#include "math.h"

Saw::Saw(float frequency, float samplerate):Oscillator(frequency, samplerate){}

void Saw::tick() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  phase += frequency / samplerate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }
  if (phase < 0.5)
  sample = 2 * phase * amplitude;
  else
  sample = -amplitude + 2 * (phase - 0.5f) * amplitude;
}
