#include <Arduino.h>

/*
   MutipleInputs.ino
   for working with an LED Bar Graph and shift registers in AVR assembler
   author: Robert Raffaele "GorrillaRibs" Miller
 */

 uint8_t inOut = 0b00011111;
 uint8_t highLow = 0b00000000;
 uint8_t compare1 = 0b00100000;
 uint8_t compare2 = 0b01000000;
 uint8_t compare3 = 0b10000000;

void setup() {
        asm (
              "sacrifice: \n" // you should know to whom
              "LDS r10, inOut \n" // load a value to send to DDRD
              "LDS r11, highLow \n" // load a value to send to portD
              "LDS r13, compare1 \n" // comparitor
              "LDS r14, compare2 \n"
              "LDS r15, compare3 \n"
              "OUT 0x0A, r10 \n" // set DDRD as mostly output, but also set an input
              "OUT 0x0B, r11 \n" // set em all low


              "poll: \n" // how many votes can I get?
              "IN r12, 0x09 \n" // get the state of portD, by checking PIND
              "CPSE r12, r11 \n"
              "RCALL lite \n"
              "RJMP poll \n"

              "lite: \n"
              "CP r12, r13 \n"
              "BREQ light1 \n"
              "afterLight1: \n"
              "CP r12, r14 \n"
              "BREQ light2 \n"
              "afterLight2: \n"
              "CP r12, r15 \n"
              "BREQ light3 \n"
              "afterLight3: \n"
              "RJMP poll \n"

              "light1: \n"
              "SBI 0x0B, 0x02 \n"
              "RCALL delay \n"
              "CBI 0x0B, 0x02 \n"
              "RJMP afterLight1 \n"

              "light2: \n"
              "SBI 0x0B, 0x03 \n"
              "RCALL delay \n"
              "CBI 0x0B, 0x03 \n"
              "RJMP afterLight2 \n"

              "light3: \n"
              "SBI 0x0B, 0x04 \n"
              "RCALL delay \n"
              "CBI 0x0B, 0x04 \n"
              "RJMP afterLight3 \n"

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


                );


}

void loop() {
}
