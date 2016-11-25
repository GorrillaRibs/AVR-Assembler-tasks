#include <Arduino.h>

/*
   NegativeInt.ino
   Purpose - To find the negative of a uint16 value
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17
 */

uint16_t value = 32;


void setup() {

Serial.begin(9600);
Serial.print("The negative of ");
Serial.print(value,BIN);
Serial.print(" is...");
asm("lds r30, value \n"
"lds r31, (value)+1 \n"
"com r30 \n"
"com r31 \n"
"adiw r30, 1 \n"
"sts value, r30 \n"
"sts (value)+1, r31 \n"
);

Serial.print(value, BIN);

}

void loop() {

}
