#include <Arduino.h>

/*
   Challenge2.ino
   Written for ATmega328p (or Arduino UNO)
   Written in Assembler because I have a death wish
   for working with an LED Bar Graph and shift registers in AVR assembler
   author: Robert Raffaele "GorrillaRibs" Miller
   Sweet lord why can't it build bob why
   like what the fuck
   why am I even doing this
 */

// The compiler still did not like this, so commented out
/*
 #define clock 0x02 // or pin 2
 #define latch 0x03 // or pin 3
 #define data 0x04 // or pin 4
 */

uint8_t data1[] = {0b11111110, 0b11111101, 0b11111011, 0b11110111, 0b111101111, 0b11011111, 0b10111111, 0b01111111};
// data for the second shift register, anodes
uint8_t data2 = 0b00000001; // data for the first shift register, cathodes I can lsl this, but not data1
// Shift registers are connected logically to matrix; i.e pin0 on the
// anode shift register is row 1 on the matrix, etc.

// data register is r11

// NOBODY CARED ABOUT ME UNTIL I PUT ON THE MASK
uint8_t mask = 0b00000001;
// "Constants", for registers lower than 15
uint8_t onee = 0x01;
uint8_t twoo = 0x02;
uint8_t threee = 0x03;
uint8_t fourr = 0x04;
uint8_t sevenn = 0x07;
uint8_t eightt = 0x08;


void setup() {
        asm (
                "load: \n"
                "LDS r1, onee \n" // loading constants for comparisons
                "LDS r2, twoo \n" // who needs registers above r15 anyways
                "LDS r3, threee \n"
                "LDS r4, fourr \n"

                "CLR r8 \n" // clear a zero register for comaparisons/clearing bytes
                "LDS r21, mask \n"  // AND mask
                "LDI r23, 0xFF \n" // load 0xFF, to set portD as output
                "LDI r25, 0x08 \n" // Use as loop counter
                "CLR r27 \n" // how many times shiftOut has looped? r27 knows
                "OUT 0x0A, r23 \n" // set portD as output
                "LDI r30, lo8(data1) \n" // WOOT INDIREKT ADDRESSES YE
                "LDI r31, hi8(data2) \n" // AREN'T THEY BEUTIFUL


                "sacrifice: \n" // To Cthulu, requires 4 goats. Also the main loop
                "LDS r11, data1 \n"
                "RCALL shiftOut\n"

                "LDS r11, data1 \n"
                "RCALL left1 \n"
                "RCALL shiftOut\n"

                "LDS r11, data1 \n"
                "RCALL left2 \n"
                "RCALL shiftOut\n"

                "LDS r11, data1 \n"
                "RCALL left3 \n"
                "RCALL shiftOut\n"

                "LDS r11, data1 \n"
                "RCALL left4 \n"
                "RCALL shiftOut\n"

                "LDS r11, data1 \n"
                "RCALL left5 \n"
                "RCALL shiftOut\n"

                "LDS r11, data1 \n"
                "RCALL left6 \n"
                "RCALL shiftOut\n"

                "LDS r11, data1 \n"
                "RCALL left7 \n"
                "RCALL shiftOut\n"

                "RJMP sacrifice \n"


                "left1: \n"
                "LSL r11 \n"
                "RET \n"

                "left2: \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "RET \n"


                "left3: \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "RET \n"


                "left4: \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "RET \n"

                "left5: \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "RET \n"


                "left6: \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "RET \n"

                "left7: \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "LSL r11 \n"
                "RET \n"


                // ** shiftOut() ** \\

                "shiftOutData: \n" // shift out the first  data var...
                "LDS r11, data1 \n"
                "RCALL shiftOut \n"

                "shiftOutData2: \n" // ...then the second...
                "LD r11, Z+ \n"
                "RCALL shiftOut \n"


                "shiftOut: \n"

                "CBI 0x0B, 0x03 \n" // set latch low
                "CBI 0x0B, 0x02 \n" // set clock low
                "MOV r15, r11 \n" // copy the data, so we dont destory it
                "AND r15, r21 \n" // mask the data, so we only get oneee byte
                "CP r15, r8 \n" // compare the ANDed data with zero
                "BREQ set0 \n" // if equal to zero, go to set0...
                "SBI 0x0B, 0x04 \n" // else, set the data pin to onee
                "RJMP back \n" // go to back

                "set0: \n"

                "CBI 0x0B, 0x04 \n" // set the data pin to zero
                "RJMP back \n" // go to back (irrelevant?)
                "back: \n"
                "DEC r25 \n" // increment the loop counter
                "CP r25, r8 \n" // see if I've looped enough
                "BREQ stopShifting \n" // go to the end
                "LSL r21 \n" // shift the mask left
                "SBI 0x0B, 0x02 \n" // set clock high
                "RJMP shiftOut \n" // jump back to the start of this loop

                // ** END OF SHIFTING ** \\

                "stopShifting: \n" // here be a label

                "INC r27 \n" // inc the loop counter
                "CP r27, r1 \n" // check if it's onee
                "BREQ shiftOutData2 \n" // shift out data2
                "SBI 0x0B, 0x03 \n" // set latch back to high
                "RET \n"

                // ** DELAYS ** \\
                // ** no explaination needed, just wasting cycles ** \\

                "delay200: \n"
                "LDI r18, 17 \n"
                "LDI r19, 60 \n"
                "LDI r20, 203 \n"
                "1: \n"
                "DEC r20 \n"
                "BRNE 1b \n"
                "DEC  r19 \n"
                "BRNE 1b \n"
                "DEC  r18 \n"
                "BRNE 1b \n"
                "NOP \n"


              ); // FUCK THIIIISSSSS

}

void loop() {
}
