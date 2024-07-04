//
// Created by PEPPY on 18/03/2024.
//

#ifndef PEPIJN_CSD_EFFECT_H
#define PEPIJN_CSD_EFFECT_H
#include <iostream>
#include "sine.h"
#include "wavetableGenerator.h"


struct Effect {
    void processFrame(const float* input, float* output) {
        float effectout = 0;
        applyEffect(input, &effectout);
        float A1 = effectout * ratio; //gonna be wet
        float A2 = *input * ( 1 - ratio);
        *output = A2 + A1;
    };
    void setDryWet(float dryWet){
        ratio = dryWet;
    }

    void setBypass(bool bypass){
        bypass = bypassbool;
    }
    virtual void applyEffect(const float* input, float* output) = 0;



private:
    float ratio = 0;
    bool bypassbool = false;

};

struct Chorus : Effect {
    float buffer[140000] = {0};
    int emptybuf = 0;
    float feedback = 0.6f;
    int delaytime = 18000 ;

    int* getdelaytime(){
        return &delaytime;
    }



    void applyEffect(const float *input, float *output) override {
        if (emptybuf <= delaytime) {
            emptybuf++;
            float tmp = *input;
            output = &tmp;
        }

        else {
            *output = (buffer[currentIndex] * feedback) + *input * (1 - feedback);
        }
        buffer[currentIndex] = *output;
        currentIndex = (currentIndex + 1) % delaytime;
    }

private:
    int currentIndex = 0;
};


struct Echo : Effect {
    float buffer[140000] = {0};
    int emptybuf = 0;
    float feedback = 0.6f;
    int echotime = 18000;

    int* getechotime(){
        return &echotime;
    }



    void applyEffect(const float *input, float *output) override {
        if (emptybuf <= echotime) {
            emptybuf++;
            float tmp = *input;
            output = &tmp;
        }

        else {
            *output = (buffer[currentIndex] * feedback) + *input * (1 - feedback);
        }
        buffer[currentIndex] = *output;
        currentIndex = (currentIndex + 1) % echotime;
    }

private:
    int currentIndex = 0;
};

struct OnePole : Effect {
    void applyEffect(const float *input, float *output) override {
        *output = (1.0f - coefficient) * *input + coefficient * feedback;
        feedback = *output;

    }

    float* getcoefficient(){
        return &coefficient;
    }


private:
    float feedback { 0.0};
    float coefficient = 0;
};


struct Tremolo : Effect {
    void applyEffect(const float *input, float *output) override {
        float modSignal = sine.genNextSample() * 0.5 + 0.5;
        modSignal *= modDepth;
        modSignal += 1.0 - modDepth;
        *output = *input * modSignal;
    }

    void setModFreq(float freq) {
        sine.setFrequency(freq);

    }

    void prepare(int samplerate) {
        sine.prepare(samplerate);
    };

    float* getmoddepth(){
        return &modDepth;
    }

private:
    float modDepth = 0;
    Sine sine{4};
};





struct Waveshaper : Effect {

    void setcurve(float curve){
        WavetableGenerator::generateSCurve(buffer, 512, curve);
    }

    void prepare(){
        WavetableGenerator::generateSCurve(buffer, 512, 10.0f);

    }

    void applyEffect(const float *input, float *output) override {
        float sample = *input;
        if (sample > 0.99999999f) sample = 0.99999999f;
        if (sample < -0.99999999f) sample = -0.99999999f;
        float indexFloat = WavetableGenerator::map(sample, -1.0f, 1.0f, 0.0f, (float) (512 - 1));
        //float indexFloat = mapInRange(sample, -1.0f, 1.0f, 0.0f, (float) (BUFFER_SIZE - 1));
        int index = (int) indexFloat;
        *output = buffer[index];
    }

    float buffer[512];
};






#endif //PEPIJN_CSD_EFFECT_H
