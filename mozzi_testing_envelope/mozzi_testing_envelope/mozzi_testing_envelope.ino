#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/sin2048_int8.h>
#include <Ead.h>
#include <EventDelay.h>
#include <mozzi_rand.h>


#define CONTROL_RATE 256

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);
EventDelay kDelay;
Ead kEnvelope(CONTROL_RATE);
int gain;
void setup() {
  // put your setup code here, to run once:
  aSin.setFreq(240);
  startMozzi(CONTROL_RATE);
  kDelay.start(1000);
}

void updateControl(){
if (kDelay.ready()) {
unsigned int duration = 1800;
unsigned int attack = 120;
unsigned int decay = duration - attack;
kEnvelope.start(attack,decay);
kDelay.start(duration+500);
}
gain = (int) kEnvelope.next();
}
  
int updateAudio(){
return (gain*aSin.next()) >> 8; 
}


void loop() {
  audioHook();

}
