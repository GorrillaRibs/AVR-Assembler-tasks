/*
Timer2Sound.ino
AVR Assembler code used to create a sound using Timer2
Code by: Robert Raffaele "GorrillaRibs" Miller
*/

#include "avr/io.h"
#define OVF 4;
#define INCR 1;

void setup() {
  Serial.begin(9600);
  asm(
".global setup \n"
    "setup: \n"
    "CLR r20 \n"
    "CLR r21 \n"
    "LDI r22, INCR \n"
    "SBI SFR_TO_ADDR(DDRB), DDB3 \n" // pin 11, output
    //Timer2 setup start
    "LDI r16, 0 \n"
    "STS TCCR2A, r16 \n"
    "LDI r16, 0b00000101" // prescaler
    "LDI r16, 1<<TOIE2 \n"
    "STS TIMSK2, r16 \n" // enable timer2 overflow
    // Timer2 setup end
    "SEI \n"
    "RET \n"


".global loop \n"
    "loop: \n"

    "CPI r20, OVF \n"
    "BRMI loop \n"
    "ADD r21, r22 \n"
    "CLR r20 \n"
    "RJMP loop \n"


".global TIMER2_OVF_vect \n"
    "TIMER2_OVF_vect: \n"

    "STS TCNT2, r22 \n"
    "INC r20 \n"
    "IN r16, _SFR_IO_ADDR(PORTB) \N"
    "LDI r25, 1<<PB3 \n"
    "EOR r16, r17 \n"
    "OUT _SFR_IO_ADDR(PORTB), r16 \n"
    "RETI \n" // yeti



  );

}

void loop() {}
