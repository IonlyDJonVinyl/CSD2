#ifndef DRUMS_H
#define DRUMS_H
#include "instrument.h"

#include <string>

class Drums:public Instrument {
private:
   std::string sound;

public:
   Drums();
   void play();
};

#endif // DRUMS_H
