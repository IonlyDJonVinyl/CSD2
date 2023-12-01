#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <string>

class Instrument {
private:
   std::string sound;

public:
   Instrument(std::string sound);
   void play();
};

#endif // INSTRUMENT_H
