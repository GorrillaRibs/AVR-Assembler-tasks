#include <Arduino.h>

/*
   SubtractionOfPowers.ino
   Purpose - Demonstrate (8-bit) Analog to Digital conversion using the
   subtraction-of-powers method
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17

*/

char bits[] = "        ";
int value = 211; // r13

void setup() {

        Serial.begin(9600);
        //Serial.print("The binary equivilent of " + String(value) + " is ");
        Serial.print("Binary Equivilent of the value is ");

        asm (
              "LDS r12, result \n" // load everything
              "LDS r13, value \n"
              "LDS r14, bit0 \n"
              "LDS r15, bit1 \n"
              "LDS r16, bit2 \n"
              "LDS r17, bit3 \n"
              "LDS r18, bit4 \n"
              "LDS r19, bit5 \n"
              "LDS r20, bit6 \n"
              "LDS r21, bit7 \n"

              "MOV r13, r22 \n" // backup data
              "MOV r21, r23 \n" // backup first thing to comare to
              "AND r13, r21 \n" // AND the data + the mask
              "CP r13, r23 \n" // compare the 2...
              "BREQ addBit7 \n" // ...and branch to another function if equal

              "testBit7: \n"
              "MOV r13, r22 \n" // again
              "MOV r20, r23 \n"
              "AND r13, r20 \n"
              "CP r13, r23 \n"
              "BREQ addBit6 \n"

              "testBit6: \n"
              "MOV r13, r22 \n" // again
              "MOV r19, r23 \n"
              "AND r13, r19 \n"
              "CP r13, r23 \n"
              "BREQ addBit5 \n"

              "testBit5: \n"
              "MOV r13, r22 \n" // again
              "MOV r18, r23 \n"
              "AND r13, r18 \n"
              "CP r13, r23 \n"
              "BREQ addBit4 \n"

              "testBit4: \n"
              "MOV r13, r22 \n" // again
              "MOV r17, r23 \n"
              "AND r13, r17 \n"
              "CP r13, r23 \n"
              "BREQ addBit3 \n"

              "testBit3: \n"
              "MOV r13, r22 \n" // again
              "MOV r16, r23 \n"
              "AND r13, r16 \n"
              "CP r13, r23 \n"
              "BREQ addBit2 \n"

              "testBit2: \n"
              "MOV r13, r22 \n" // again
              "MOV r15, r23 \n"
              "AND r13, r15 \n"
              "CP r13, r23 \n"
              "BREQ addBit1 \n"

              "testBit1: \n"
              "MOV r13, r22 \n" // again
              "MOV r14, r23 \n"
              "AND r13, r14 \n"
              "CP r13, r23 \n"
              "BREQ addBit0 \n"


              "addBit7: \n"
              "ADD r12, r21 \n" // add the bit to the result
              "MOV r22, r13 \n"
              "MOV r23, r21 \n"
              "SUB r13, r21 \n" // subtract the power from the value
              "RCALL testBit7 \n"

              "addBit6: \n"
              "ADD r12, r20 \n"
              "MOV r22, r13 \n"
              "MOV r23, r21 \n"
              "SUB r13, r20 \n"
              "RCALL testBit6 \n"

              "addBit5: \n"
              "ADD r12, r19 \n"
              "MOV r22, r13 \n"
              "MOV r23, r21 \n"
              "SUB r13, r19 \n"
              "RCALL testBit5 \n"

              "addBit4: \n"
              "ADD r12, r18 \n"
              "MOV r22, r13 \n"
              "MOV r23, r21 \n"
              "SUB r13, r18 \n"
              "RCALL testBit4 \n"

              "addBit3: \n"
              "ADD r12, r17 \n"
              "MOV r22, r13 \n"
              "MOV r23, r21 \n"
              "SUB r13, r17 \n"
              "RCALL testBit3 \n"

              "addBit2: \n"
              "ADD r12, r16 \n"
              "MOV r22, r13 \n"
              "MOV r23, r21 \n"
              "SUB r13, r16 \n"
              "RCALL testBit2 \n"

              "addBit1: \n"
              "ADD r12, r15 \n"
              "MOV r22, r13 \n"
              "MOV r23, r21 \n"
              "SUB r13, r15 \n"
              "RCALL testBit1 \n"

              "addBit0: \n"
              "ADD r12, r14 \n"
              "MOV r22, r13 \n"
              "MOV r23, r21 \n"
              "SUB r13, r14 \n"
              "RCALL saveResult \n"

              "saveResult: \n"
              "STS result, r12 \n"

              );
        Serial.print("The result is");
        Serial.println(result);

}

void loop() {
}
