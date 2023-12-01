#include "instrument.h"
#include <iostream>

Instrument::Instrument(std::string sound) {
   this->sound = sound;
}

void Instrument::play() {
   std::cout << this->sound << std::endl;
}
