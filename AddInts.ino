#include <Arduino.h>

/*
   AddInts.ino
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17
 */

uint16_t opA = 0xFFF;
uint16_t opB = 0xFF;
uint32_t sum;

void setup() {
        Serial.begin(9600);
        asm ("LDS r20, opA \n"
             "LDS r21, opA+1 \n"
             "CLR r22 \n"
             "LDS r23, opB \n"
             "LDS r24, opB+1 \n"
             "CLR r25 \n"
             "ADD r20, r23 \n"
             "ADC r21, r24 \n"
             "ADC r25, r25 \n"
             "STS sum, r20 \n"
             "STS sum+1, r21 \n"
             "STS sum+2, r25 \n"
             );
        Serial.print(String(opA) + " + " + String(opB) + " = " + String(sum));
}

void loop() {
}
