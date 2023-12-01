#ifndef PIANO_H
#define PIANO_H
#include "instrument.h"

#include <string>

class Piano:public Instrument {
private:
   std::string sound;

public:
   Piano(std::string sound);
   void play();
};

#endif // PIANO_H
