#include "square.h"
#include "math.h"

Square::Square(float frequency, float samplerate):Oscillator(frequency, samplerate){}

void Square::tick() {
  // NOTE 1. - frequency / SAMPLERATE can be implemented in a more efficient way
  phase += frequency / samplerate;
  if(phase > 1.0f) {
    phase -= 1.0f;
  }
  if (phase < 0.5)
  sample = amplitude;
  else
  sample = -amplitude;
}
