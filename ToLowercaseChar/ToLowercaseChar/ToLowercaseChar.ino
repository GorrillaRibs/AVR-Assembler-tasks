#include <Arduino.h>

/*
   ToLowercaseChar.ino
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17
 */

uint8_t inLetter = 'A';
uint8_t outLetter;

void setup() {

        Serial.begin(9600);
        Serial.print("The lowercase version of " + String((char) inLetter) + " is ");

        asm ("LDS r31, inLetter \n"
             "ORI r31, 0x20 \n"
             "STS outLetter, r31 \n");

        Serial.print(String((char) outLetter));

}

void loop() {
}
