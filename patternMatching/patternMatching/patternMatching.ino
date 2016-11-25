#include <Arduino.h>

/*
   patternMatching.ino
   Purpose - To search for a particular sequence in a byte
   using the instructions AND, CP, LSR, and MOV
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17
 */

uint8_t data = 0b11011011; // 219 in decimal
uint8_t pattern = 0b00000011; // 11 in decimal
uint8_t patternLength = 2;
uint8_t count = 0;
uint8_t loopCount = 4;
uint8_t currentLoop = 0;

void setup() {

        Serial.begin(9600);
        Serial.print("Data: ");
        Serial.print(data,BIN);
        Serial.print("\tPattern: ");
        Serial.print(pattern,BIN);
        Serial.println();
        Serial.print("Count: ");

        asm ("LDS r13, loopCount \n" // load various variables into from SRAM
             "LDS r14, currentLoop \n"
             "LDS r15, count \n"
             "LDS r16, data \n"
             "LDS r18, pattern \n"
             "MOV r17, r18 \n"
             "MOV r16, r19 \n"
             "LOOP: \n"
             "INC r14 \n"
             "AND r16, r17 \n"
             "CP r16, r17 \n"
             "BREQ dontInc \n"
             "INC r15 \n"
             "dontInc: \n"
             "LSR r16 \n"
             "MOV r17, r18 \n"
             "MOV r16, r19 \n"
             "CP r13, r14 \n"
             "BRNE LOOP \n"
             "STS count, r15 \n");

        Serial.print(count);
}


void loop() {
}
