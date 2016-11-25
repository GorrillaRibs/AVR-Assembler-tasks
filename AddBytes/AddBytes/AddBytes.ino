#include <Arduino.h>

/*
   AddBytes.ino
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17
 */

uint8_t opA = 204;
uint8_t opB = 205;
uint16_t sum = 0;

void setup() {
        Serial.begin(9600);
        asm ("LDS r20, opA \n"
             "CLR r21 \n"
             "LDS r22, opB \n"
             "CLR r23 \n"
             "ADD r20, r22 \n"
             "ADC r21, r23 \n"
             "STS sum, r20 \n"
             "STS sum+1, r21 \n"
             );

        Serial.print(String(opA) + " + " + String(opB) + " = " + String(sum));

}

void loop() {
}
