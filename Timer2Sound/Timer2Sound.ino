/*
Timer2Sound.ino
AVR Assembler code used to create a sound using Timer2
Code by: Robert Raffaele "GorrillaRibs" Miller
*/

#include "avr/io.h"

void setup() {
  Serial.begin(9600);
  asm(
    "start: \n"
    "CLR r19 \n"
    "CLR r20 \n"
    "LDI r22, 0XFF \n"
    "SBI SFR_TO_ADDR(DDRB), DDB3 \n"
    "LDI r16, 0x40 \n" // leave space to have a prescaler if we want one
    "STS TCCR2A, r16 \n"
    "LDI r16, 1<<TOIE2 \n"
    "STS TIMSK2, r16 \n" // enable timer2 overflow
    
    "SEI \n"


    "loop: \n"
    "CP r22, r20 \n"
    "BRGE onOff \n"

    "RJMP loop \n"


    "onOff: \n"
    "SBI SFR_TO_ADDR(DDRB), DDB3 \n"
    "CBI SFR_TO_ADDR(DDRB), DDB3 \n"
    "RET \n"

    ".global TIMER2_OVF_vect \n"
    "TIMER2_OVF_vect: \n"
    "INC r20 \n"
    "RETI \n" // yeti



  );

}

void loop() {}
