#include <Arduino.h>

/*
   ANDMask.ino
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17
 */

uint8_t data = 0b01011001;

void setup() {
        Serial.begin(9600);
        asm ("LDS r31, data \n"
             "ANDI r31, 0x0F \n"
             "STS data, r31 \n");
        Serial.print(data, BIN);
}

void loop() {
}
