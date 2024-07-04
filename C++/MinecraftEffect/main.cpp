
#include "audiocomponent.h"
#include <iostream>
#include "oscillator.h"
#include "Effect.h"
#include "osc.h"
using namespace std;

class OscCallback : public OSC {

    int realcallback(const char *path,const char *types,lo_arg **argv,int argc)
    {
        string msgpath=path;

        cout << "path: " << msgpath << endl;
        if(!msgpath.compare("/fx/peppymod/depth")){
            int depth = argv[0]->i;
            cout << "Message:" << depth << endl;
            if (depth < 70 ){
                *tremolo->getmoddepth() = (1- ((depth + 64.0f) / 134.0f));
                tremolo->setModFreq(1.f + (depth + 64.0f) * (39.8f / 134.0f));
            }
            else{
                *tremolo->getmoddepth() = 0;
                tremolo->setModFreq(0);
            }
        }


        if(!msgpath.compare("/fx/peppymod/submerged")){
            float submerged = min(argv[0]->f, 4.9f);
            cout << "Message:" << submerged << endl;
            *coefficient = pow(submerged / 5.0f, 2.f);
        }


        if(!msgpath.compare("/fx/peppymod/caveyness")){
            float caveyness = argv[0]->f;
            cout << "Message:" << caveyness << endl;
            echo->setDryWet( caveyness / 29);
            *echo->getechotime() = ((60000.0f * caveyness) / 30.0f)+1;
        }


        if(!msgpath.compare("/fx/peppymod/health")){
            float health = argv[0]->f;
            cout << "Message:" << health << endl;
            waveshaper->setDryWet(1);
            waveshaper->setcurve(10 - (health * 0.50));

        }



    }

public:
    void init_effect_variables(int *delaytime, float *coefficient, Echo *echo, Tremolo *tremolo, Waveshaper *waveshaper) {
        this->delaytime = delaytime;
        this->coefficient = coefficient;
        this->echo = echo;
        this->tremolo = tremolo;
        this->waveshaper = waveshaper;
    }
private:
    int* delaytime;
    float* coefficient;
    int* echotime;
    Tremolo* tremolo;
    Echo* echo;
    Waveshaper* waveshaper;


};


struct CustomCallback : AudioCallback {
    explicit CustomCallback(double Fs) : AudioCallback(Fs) {
    }



    void prepare(int sampleRate, int blockSize) override {

        osc.init("7000");
        osc.init_effect_variables(chorus.getdelaytime(), filter.getcoefficient(), &echo, &tremolo, &waveshaper);
        filter.setDryWet(1);
        tremolo.setDryWet(1);
        osc.set_callback("/fx/peppymod/depth", "i");
        osc.set_callback("/fx/peppymod/submerged", "f");
        osc.set_callback("/fx/peppymod/caveyness", "f");
        osc.set_callback("/fx/peppymod/food", "i");
        osc.set_callback("/fx/peppymod/health", "f");
        osc.start();
        tremolo.prepare(sampleRate);
        waveshaper.prepare();
    }

    void process(AudioBuffer buffer) override {
        auto [inputChannels, outputChannels, numInputChannels, numOutputChannels, numFrames] = buffer;


        for (auto sample = 0u; sample < numFrames; ++sample) {

            framepass++;
            for(auto channel = 0u; channel < numOutputChannels; ++channel) {
                echo.processFrame(&inputChannels[channel][sample], &outputChannels[channel][sample]);
                filter.processFrame(&outputChannels[channel][sample], &outputChannels[channel][sample]);
                tremolo.processFrame(&outputChannels[channel][sample], &outputChannels[channel][sample]);
                waveshaper.processFrame(&outputChannels[channel][sample], &outputChannels[channel][sample]);




            }
        }
    }

    unsigned long long framepass = 0;

    Chorus chorus;
    OscCallback osc;
    OnePole filter;
    Echo echo;
    Tremolo tremolo;
    Waveshaper waveshaper;
};

#define Delta_Sequence 0

int main() {


#if Delta_Sequence
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource(48000);
    DeltaSequence::run(audioSource.filter);
#else
    ScopedMessageThreadEnabler scopedMessageThreadEnabler;
    CustomCallback audioSource(48000);
    JUCEModule juceModule(audioSource);
    juceModule.init(2, 2);


    std::cout << "Press q Enter to quit..." << std::endl;
    bool running = true;
    while (running) {
        switch (std::cin.get()) {
            case 'q':
                running = false;
                break;
        }
    }
#endif
    return 0;
}
