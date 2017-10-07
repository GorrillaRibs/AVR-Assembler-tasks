; RSGC ACES 2017
; Sonar Assembler Project
; By RM, ST, and SA

#include "avr/io.h"
#include <ASCII.h>
#define BAUD9600 103           //(((F_CPU / (BAUDRATE * 16))) - 1)

; All Serial functions load off of Regs 24 & 25

;gpLabel:
;.asciz  "32 GP Registers:\n"

; No less than 7 sacrifices to Cthulu required to function
.global setup
setup:
CLR r17
CALL Timer1Setup
LDI r25,BAUD9600 >> 8       ; pass the preferred BAUD rate to the initUART function
LDI r24,BAUD9600            ;
CALL initUART               ;
RET

.global Timer1Setup
Timer1Setup:
CLI
PUSH r16
SBI _SFR_IO_ADDR(DDRB), DDB2
LDI r16, (1<<COM1B1)|(1<<COM1B0)|(1<<WGM11)
STS TCCR1A, r16
LDI r16, (1<<CS11)|(1<<WGM13)|(1<<WGM12)
STS TCCR1B, r16
LDI r16, 0x9C
STS ICR1H, r16
LDI r16, 0x3F
STS ICR1L, r16
LDI r16, 0x98
STS OCR1BH, r16
LDI r16, 0xBB
STS OCR1BL, r16
LDI r16, (1<<TOIE1)
STS TIMSK1,r16
POP r16
SEI
RET

.global loop
loop:
RJMP loop

.global TIMER1_OVF_vect
TIMER1_OVF_vect:
INC r17
SBRS r17, 0
RJMP even

odd:
LDI r16, 0x86 ; 34331
STS OCR1BH, r16
LDI r16, 0x1B
STS OCR1BL, r16
RJMP end

even:
LDI r16, 0x97 ; 38827
STS OCR1BH, r16
LDI r16, 0xAB
STS OCR1BL, r16

end:
CALL delay
RETI // YETI

; Courtesy of AVR Delay creater
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
