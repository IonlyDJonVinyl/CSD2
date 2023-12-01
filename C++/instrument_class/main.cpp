#include "instrument.h"

int main() {
   Instrument instrument1("BADDADAN");
   Instrument instrument2("BADDADAN 2x");

   instrument1.play();
   instrument2.play();

   return 0;
}
