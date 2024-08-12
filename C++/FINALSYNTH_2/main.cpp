#include "sine.h"
#include "square.h"
#include "saw.h"
#include <iostream>
#include <thread>
#include "jack_module.h"
#include "math.h"
#include "tripleosc.h"
#include "utils.h"
#include "modulator.h"
#include "fmosc.h"

class MelodyGenerator {
public:
    MelodyGenerator(float sampleRate) : sampleRate(sampleRate) {}

    void addNote(int note, float duration, float amplitude) {
        notes.push_back(note);
        durations.push_back(duration);
        amplitudes.push_back(amplitude);
    }

    void setSampleRate(float sr) {
        sampleRate = sr;
    }

    void play() {
        time = 0;
    }

    void tick(Synthesizer* synth, Synthesizer* synth2) {
        time+=1.0f/sampleRate;
        float startAt = 0;
        for (int i = 0; i < notes.size(); i++) {
            float duration = durations[i];
            float endAt = startAt+duration;
            if (startAt <= time && endAt > time) {
                synth->setNote(notes[i]);
                synth2->setNote(notes[i]);
                synth->setAmplitude(amplitudes[i]*amplitude);
                synth2->setAmplitude(amplitudes[i]*amplitude);
                return;
            }
            startAt += duration;
        }
        synth->setAmplitude(0);
        synth2->setAmplitude(0);
    }

    void setAmplitude(float amp) {
        amplitude = amp;
    }

    void clear() {
        time = 0;
        notes.clear();
        durations.clear();
        amplitudes.clear();
    }

private:
    std::vector<int> notes;
    std::vector<float> durations;
    std::vector<float> amplitudes;

    float sampleRate;
    float time = 0;
    float amplitude = 1;
};

class CustomCallback : public AudioCallback {
public:
  void prepare(int rate) override {
    samplerate = (float) rate;
    sine.setSamplerate(samplerate);
    osc.setSampleRate(samplerate);
    modSine.setSamplerate(samplerate);
    oscSine.setSamplerate(samplerate);
    modSine.setAmplitude(2);
    mg.setSampleRate(samplerate);
    mg.play();
    std::cout << "\nsamplerate: " << samplerate << "\n";
  }

  void process(AudioBuffer buffer) override {
    for (int i = 0; i < buffer.numFrames; ++i) {
      // write sample to buffer at channel 0, amp = 0.25
      //buffer.outputChannels[0][i] = sine.getSample();
      //sine.tick();
      mg.tick(&osc, &mod);
      mod.tick();
      buffer.outputChannels[0][i] = (osc.getSample()+mod.getSample())*0.5;
      osc.tick();
    }
  }

  TripleOsc* getTripleOsc() {
    return &osc;
  }

  void setTripleOsc(TripleOsc tripleOsc) {
    osc = tripleOsc;
  }

  MelodyGenerator* getMelodyGenerator() {
    return &mg;
  }

  Fmosc* getModulator() {
    return &mod;
  }

  private:
  float samplerate = 48000;
  Square sine = Square(220, samplerate);
  TripleOsc osc = TripleOsc(60, 1, 0, 2, 12, 3, 0, samplerate); // 1st = MIDI, 2nd = OSC Type 1, 3th = offset Type 1 4th = OSC Type 2 5th = offset Type 2 6th = OSC Type 3, 7th = offset Type 3. 
  
  Sine modSine = Sine(8, samplerate);
  Sine oscSine = Sine(440, samplerate);
  Fmosc mod = Fmosc(&oscSine, &modSine, samplerate);
  
  MelodyGenerator mg = MelodyGenerator(samplerate);
};

int main(int argc,char **argv)
{
  auto callback = CustomCallback {};
  auto mg = callback.getMelodyGenerator();
  mg->addNote(60, 0.25, 0.2);
  mg->addNote(64, 0.25, 0.4);
  mg->addNote(67, 0.25, 0.6);
  mg->addNote(72, 0.25, 1);
  auto jackModule = JackModule { callback };
  float master = 0.3f;
  mg->setAmplitude(master);

  jackModule.init (0, 1);

  sleep(1);
  mg->clear();

        std::cout<<"_______________________________________________________________"<<std::endl;
        std::cout<<"|                         PEPPY SYNTH                         |"<<std::endl;
        std::cout<<"|_____________________________________________________________|"<<std::endl;
        std::cout<<"  USER MANUAL:                                                 "<<std::endl;
        std::cout<<"  Tree oscillators are being used.                             "<<std::endl;
        std::cout<<"  type the 'osc' command followed by the designated osc type x3"<<std::endl;
        std::cout<<"  E.G: osc sine 0 sine -12 saw 8                               "<<std::endl; 
        std::cout<<"                                                               "<<std::endl; 
        std::cout<<"  type the midi command followed by the designated MIDI number,"<<std::endl;
        std::cout<<"  duration and amplitude                                       "<<std::endl; 
        std::cout<<"  E.G: midi  72 1 0.5                                          "<<std::endl; 
        std::cout<<"  E.G: midi  65 2 0.7                                          "<<std::endl; 
        std::cout<<"  make this list as long as you want                           "<<std::endl;
        std::cout<<"                                                               "<<std::endl; 
        std::cout<<"  CONTROL COMMANDS:                                            "<<std::endl; 
        std::cout<<"  + = volume up                                                "<<std::endl; 
        std::cout<<"  - = volume down                                              "<<std::endl;  
        std::cout<<"  q = quit                                                     "<<std::endl;
        std::cout<<"  play = start melody                                          "<<std::endl;
        std::cout<<"  clear = clear melody                                         "<<std::endl;

  bool running = true;
  while (running) {
      std::string line;
      std::getline(std::cin, line);
      if (line == "q") {
        running = false;
      } else if (line.rfind("osc ", 0) == 0){
        std::vector<std::string> words = split(line, ' ');
        std::string osc1Type = words[1];
        float osc1Offset = std::stof(words[2]);
        std::string osc2Type = words[3];
        float osc2Offset = std::stof(words[4]);
        std::string osc3Type = words[5];
        float osc3Offset = std::stof(words[6]);
        
        int osc1;
        int osc2;
        int osc3;
        if (osc1Type.compare("sine")==0) {
            osc1 = 1;
        } else if (osc1Type.compare("saw")==0) {
            osc1 = 2;
        } else if (osc1Type.compare("square")==0) {
            osc1 = 3;
        }
        
        if (osc2Type.compare("sine")==0){
            osc2 = 1;
        } else if (osc2Type.compare("saw")==0){
            osc2 = 2;
        } else if (osc2Type.compare("square")==0){
            osc2 = 3;
        }
        
        if (osc3Type.compare("sine")==0) {
            osc3 = 1;
        } else if (osc3Type.compare("saw")==0) {
            osc3 = 2;
        } else if (osc3Type.compare("square")==0) {
            osc3 = 3;
        }

        callback.getTripleOsc()->pause();
        sleep(1);
        callback.getTripleOsc()->change(osc1, osc1Offset, osc2, osc2Offset, osc3, osc3Offset);
        callback.getTripleOsc()->resume();
      } else if (line.rfind("midi ", 0) == 0){
        auto words = split(line, ' ');
        mg->addNote(std::stoi(words[1]), std::stof(words[2]), std::stof(words[3]));
      } else if (line == "+"){
        master = master + 0.1;
        mg->setAmplitude(master);
      } else if (line == "-"){
        master = master - 0.1;
        mg->setAmplitude(master);
      } else if (line.compare("play")==0){
        mg->play();
      } else if (line.compare("clear")==0){
        mg->clear();
      } else {}

  }

  //end the program
  return 0;
} // main()
