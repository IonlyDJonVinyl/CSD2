#ifndef _TRIPLE_OSC_H_
#define _TRIPLE_OSC_H_

#include "synthesizer.h"
#include "oscillator.h"

class TripleOsc : public Synthesizer {

public:
    TripleOsc(int note, int osc1, float off1, int osc2, float off2, int osc3, float off3, float sampleRate);
    ~TripleOsc();

    void tick() override;
    void setNote(int note) override;
    void change(int osc1, float off1, int osc2, float off2, int osc3, float off3);

private:
    Oscillator* oscs[3];
    float offsets[3];

};

#endif