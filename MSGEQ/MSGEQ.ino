// Code by Robert Raffaele "GorrillaRibs" Miller

#include "MSGEQ7.h"
#define pinAnalog A1 // input
#define pinReset 0
#define pinStrobe 1
#define MSGEQ7_INTERVAL ReadsPerSecond(50)
#define MSGEQ7_SMOOTH 191 // Range: 0-255

CMSGEQ7<MSGEQ7_SMOOTH, pinReset, pinStrobe, pinAnalog> MSGEQ7;

#define pinLed 3

void setup() {

  MSGEQ7.begin();
  //setup for 1 LED
  pinMode(pinLed, OUTPUT);

}



void loop() {
  bool newReading = MSGEQ7.read(MSGEQ7_INTERVAL);

  if (newReading) {
    // Read bass frequency
    uint8_t input = MSGEQ7.get(MSGEQ7_BASS);

    // Output PWM signal via Led to the music beat
    analogWrite(pinLed, input);

  }

}
