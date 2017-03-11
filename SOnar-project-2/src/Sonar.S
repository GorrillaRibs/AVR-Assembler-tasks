; RSGC ACES 2017
; Sonar Assembler Project
; By RM, ST, and SA

#include "avr/io.h"
#include <ASCII.h>
#define BAUD9600 103           //(((F_CPU / (BAUDRATE * 16))) - 1)
#define data 65                //ASCII value translates to 'A' or '\A
#define trig PB1
#define echo PB0
#define hi 0
#define lo 0

;gpLabel:
;.asciz  "32 GP Registers:\n"

; No less than 7 sacrifices to Cthulu required to function
.global setup
setup:
CALL Timer1Setup
LDI r25,BAUD9600 >> 8       ; pass the preferred BAUD rate to the initUART function
LDI r24,BAUD9600            ;
CALL initUART               ;
RET

.global Timer1Setup
Timer1Setup:
CLI
; setup for normal mode and interupt
LDI r16, 0 ; prepare for Normal Mode //sets pin to toggle on 9
STS TCCR1A, r16 ; set Normal Mode, now configure the prescaler...
LDI r16, 0b00000011 ; T1:2^24/2^10/2^16 (prescale) > 0.25 ovf/s > 0.125Hz
STS TCCR1B, r16 ; Timer1 clock = system clock / prescale
LDI r16,hi ; load TCNT1 (Timer1's 2-byte counter)
STS TCNT1H,r16 ; T1:2^16-(2^24/2^8/120)=64989=0xFDDD->120ovf/s=60Hz
LDI r16,lo ; LED flashing at 24Hz does not seem to produce PoV
STS TCNT1L,r16 ; even at 60Hz there appears to be some noticeable flicker
LDI r16, 1<<ICIE1 | 1<<TOIE1  ; enable the input capture and OVF interupt
STS TIMSK1, r16
SEI
RET

.global loop
loop:
RJMP loop

.global TIMER1_OVF_vect
TIMER1_OVF_vect:
LDI r16,hi ; load TCNT1 (Timer1's 2-byte counter)
STS TCNT1H,r16 ; T1:2^16-(2^24/2^8/120)=64989=0xFDDD->120ovf/s=60Hz
LDI r16,lo ; LED flashing at 24Hz does not seem to produce PoV
STS TCNT1L,r16 ; even at 60Hz there appears to be some noticeable flicker
IN r16,_SFR_IO_ADDR(PORTB) ; read the port
LDI r17,1<<trig ; prepare the bit(s) to toggle
EOR r16,r17 ; toggle the bit(s), leaving the others unaffected
OUT _SFR_IO_ADDR(PORTB),r16 ; update the port
MOV r25, r16 // DATA?????
CALL printChar
CALL printLn
RETI // YETI

delay:
ldi  r19, 61
ldi  r20, 225
ldi  r21, 64
L1:
dec  r21
brne L1
dec  r20
brne L1
dec  r19
brne L1
ret
