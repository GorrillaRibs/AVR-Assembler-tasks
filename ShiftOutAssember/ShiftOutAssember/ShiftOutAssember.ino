#include <Arduino.h>

/*
   ShiftOutAssembler.ino
   TEI3M 15/16 exam, but in AVR assembler
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17
 */

// defining pin names in a vain attempt to make asm readable
// clock is 0x02, or pin 2
// latch is 0x03, or pin 3
// data is 0x04, or pin 4

// some variables
uint8_t LEDs = 12; // amount of LEDs
uint8_t data1 = 0xAA; // for first shift register
uint8_t data2 = 0; // second shift register
uint8_t data3 = 0; // third shift register
uint8_t shiftIt = 0; // value to shift out (r14)
uint8_t temp1 = 0;
uint8_t temp2 = 0;
uint8_t temp3 = 0;
// NOBODY CARED ABOUT ME UNTIL I PUT ON THE MASK
uint8_t mask = 0b00000001;

void setup() {
    //    Serial.begin(9600);
        asm (
                "CLR r8 \n" // clear registers for later use
                "LDI r25, 0x08 \n" // Use as loop counter
                "LDS r11, data1 \n"
                "LDS r14, shiftIt \n"
                "LDS r21, mask \n"
                "LDI r23, 0xFF \n"
                "OUT 0x0A, r23 \n" // set portD as output
                "CBI 0x0B, 0x03 \n" // set latch low

                "keepGoing: \n"

                "shiftOut: \n"
                "CBI 0x0B, 0x02 \n" // set clock low
                "MOV r15, r11 \n" // backup the data
                "AND r15, r21 \n" // mask the data, so we only get one byte
                "CP r15, r8 \n" // compare the ANDed data with zero
                "BREQ set0 \n" // if equal to zero
                "SBI 0x0B, 0x04 \n"
                "RJMP back \n"

                "set0: \n"
                "CBI 0x0B, 0x04 \n"
                "RJMP back \n"

                "back: \n"
                "DEC r25 \n" // increment the loop counter
                "CP r25, r8 \n" // see if I've looped enough
                "BREQ stopShifting \n" // go back to the start
                "LSL r21 \n" // shift the mask left
                "SBI 0x0B, 0x02 \n" // set clock high
                "RJMP shiftOut \n" // jump back to the start of this loop


                "stopShifting: \n" // here be a label
                "SBI 0x0B, 0x03 \n"
                "NOP \n" // nope

                );
      //  Serial.println("done");

}

void loop() {
}
