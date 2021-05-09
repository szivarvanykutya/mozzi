/*  Example playing a sinewave at a set frequency,
    using Mozzi sonification library.

    Demonstrates the use of Oscil to play a wavetable.

    Circuit: Audio output on digital pin 9 on a Uno or similar, or
    DAC/A14 on Teensy 3.1, or
    check the README or http://sensorium.github.io/Mozzi/

    Mozzi documentation/API
		https://sensorium.github.io/Mozzi/doc/html/index.html

		Mozzi help/discussion/announcements:
    https://groups.google.com/forum/#!forum/mozzi-users

    Tim Barrass 2012, CC by-nc-sa.
*/

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/sin2048_int8.h> // sine table for oscillator



// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aSin(SIN2048_DATA);
Oscil <SIN2048_NUM_CELLS, CONTROL_RATE> kSin(SIN2048_DATA);

byte volume;
byte kFreq;
const char INPUT_PIN = 0 ;

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 64 // Hz, powers of 2 are most reliable


void setup(){
  
  aSin.setFreq(440); // set the frequency
  kSin.setFreq(4);
  startMozzi(CONTROL_RATE); // :)

}


void updateControl(){
  // put changing controls in here
  
  int sensor_val = mozziAnalogRead(INPUT_PIN);
  kFreq= map(sensor_val,0,1023,1,64);
  kSin.setFreq(kFreq);
  volume=(kSin.next()>>2)+127;
  
}


AudioOutput_t updateAudio(){
  return aSin.next()*volume >> 8; // return an int signal centred around 0
}


void loop(){
  audioHook(); // required here
}
