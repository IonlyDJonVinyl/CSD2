#include "instrument.h"
#include "piano.h"
#include "drums.h"


int main() {
   Instrument piano = Piano("Pling");
   Instrument drums = Drums();

   piano.play();
   drums.play();

   return 0;
}
