#include <Arduino.h>

/*
   LEDMatrixGame.ino
   'move' an LED around a matrix using buttons (up, down, left, and right)
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17
 */

// defining pin names in a vain attempt to make asm readable
// clock is 0x01, or pin 1
// latch is 0x02, or pin 2
// data is 0x03, or pin 3

/* Buttons are:
  UP: Pin 4
  DOWN: Pin 5
  LEFT: Pin 6
  RIGHT: Pin 7
*/

// some variables
uint8_t LEDs = 12; // amount of LEDs
uint8_t data1 = 0b00000001; // for first shift register
uint8_t data2 = 0b11111110; // second shift register
uint8_t inOut = 0b00001111;

// foor checking when the buttons are pressed
uint8_t button1 = 0b00010000;
uint8_t button2 = 0b00100000;
uint8_t button3 = 0b01000000;
uint8_t button4 = 0b10000000;

/*
Shift register 1 - cathodes
Shift register 2 - anodes
*/

// NOBODY CARED ABOUT ME UNTIL I PUT ON THE MASK
uint8_t mask = 0b00000001;

// Some other variables, so I can load registers under 15
// with 'constants'
uint8_t one = 0x01;
// uint8_t two = 0x02;
// uint8_t three = 0x03;

void setup() {

        asm (
                "CLR r8 \n" // clear registers for later use
                "LDI r25, 0x08 \n" // Use as loop counter
                "LDS r1, one \n"
                "LDS r5, inOut \n"

                "LDS r6, button1 \n"
                "LDS r7, button2 \n"
                "LDS r8, button3 \n"
                "LDS r9, button4 \n"
                "MOV r6, r13 \n"
                "MOV r7, r14 \n"
                "MOV r8, r16 \n"
                "MOV r9, r17 \n"

                "LDS r21, mask \n"
                "LDI r23, 0xFF \n"
                "OUT 0x0A, r23 \n" // set portD as output
                "CBI 0x0B, 0x03 \n" // set latch low

                "OUT 0x0A, r5 \n" // set DDRD as output for shifting and
                                  // input for buttons

                "buttons: \n"

                "IN r12, 0x09 \n"
                "AND r6, r12 \n"
                "CPSE r6, r13 \n"
                "RCALL buttonUp \n"

                "IN r12, 0x09 \n"
                "AND r7, r12 \n"
                "CPSE r7, r14 \n"
                "RCALL buttonDown \n"

                "IN r12, 0x09 \n"
                "AND r8, r12 \n"
                "CPSE r8, r16 \n"
                "RCALL buttonRight \n"

                "IN r12, 0x09 \n"
                "AND r9, r12 \n"
                "CPSE r9, r17 \n"
                "RCALL buttonLeft \n"

                "RJMP buttons \n"



                "buttonUp: \n"
                "LDS r11, data1 \n"
                "ROL r11 \n"
                "BRCS ROLagain \n"
                "STS data1, r11 \n"
                "RCALL shiftOutData \n"
                "RET \n"

                "buttonDown: \n"
                "LDS r11, data1 \n"
                "ROR r11 \n"
                "BRCS RORagain \n"
                "STS data1, r11 \n"
                "RCALL shiftOutData \n"
                "RET \n"

                "buttonLeft: \n"
                "LDS r11, data2 \n"
                "ROL r11 \n"
                "BRCC ROLagain \n"
                "STS data2, r11 \n"
                "RCALL shiftOutData \n"
                "RET \n"

                "buttonRight: \n"
                "LDS r11, data2 \n"
                "ROR r11 \n"
                "BRCC RORagain \n"
                "STS data2, r11 \n"
                "RCALL shiftOutData \n"
                "RET \n"


                "RORagain: \n"
                "ROR r11 \n"
                "RET \n"

                "ROLagain: \n"
                "ROL r11 \n"
                "RET \n"


                "shiftOutData: \n"
                "LDS r11, data2 \n"
                "RCALL shiftOut \n"

                "shiftOutData2: \n"
                "LDS r11, data1 \n"
                "RCALL shiftOut \n"


                "shiftOut: \n"
                "CBI 0x0B, 0x01 \n" // set clock low
                "MOV r15, r11 \n" // backup the data
                "AND r15, r21 \n" // mask the data, so we only get one byte
                "CP r15, r8 \n" // compare the ANDed data with zero
                "BREQ set0 \n" // if equal to zero
                "SBI 0x0B, 0x03 \n"
                "RJMP back \n"

                "set0: \n"
                "CBI 0x0B, 0x02 \n"
                "RJMP back \n"

                "back: \n"
                "DEC r25 \n" // increment the loop counter
                "CP r25, r8 \n" // see if I've looped enough
                "BREQ stopShifting \n" // go back to the start
                "LSL r21 \n" // shift the mask left
                "SBI 0x0B, 0x01 \n" // set clock high
                "RJMP shiftOut \n" // jump back to the start of this loop


                "stopShifting: \n" // here be a label
                "INC r10 \n"
                "CP r10, r1 \n"
                "BREQ shiftOutData2 \n"
                "SBI 0x0B, 0x02 \n"
                "NOP \n" // nope
                "RET \n"


                // ** DELAYS ** \\
                // ** no explaination needed, just wasting cycles ** \\

                "delay: \n"
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
                "RET \n"

                );

}

void loop() {
}
