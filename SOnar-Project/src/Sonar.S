; RSGC ACES 2017
; Sonar Assembler Project
; By RM, ST, and SA

#include "avr/io.h"
#include <ASCII.h>
#define BAUD9600 103           //(((F_CPU / (BAUDRATE * 16))) - 1)
#define data 65                //ASCII value translates to 'A' or '\A

;gpLabel:
;.asciz  "32 GP Registers:\n"

; No less than 7 sacrifices to Cthulu required to function
.global setup
setup:
CLI
CLR r17
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
SEI
RET
/*
SBI _SFR_IO_ADDR(DDRB), DDB1

; Set a pin to input for the data from ultrasonic sensor

LDI r16, (1 << COM1A0) | (1 << WGM13) | (1 << WGM12) | (1 << WGM11) | (1 << WGM10)
; Timer setup starts
STS TCCR1A, r16
STS TCNT1H, r16  ; high byte
STS TCNT1L, r16  ; low byte
LDI r16, 0x04
STS TCCR1B, r16  ; load a prescaler
LDI r16, 1 << TOIE1
STS TIMSK1, r16
; Timer setup ends


; Connect the 'trigger' pin on the ultrasonic seonsor, so the pulse on this pin triggers it
LDI r16, 0xFF
STS OCR1AH, r16  ; high byte
LDI r16, 0xFF
STS OCR1AL, r16  ; low byte

SEI ; Turn interupts on

*/


LDI r25,BAUD9600 >> 8       ; pass the preferred BAUD rate to the initUART function
LDI r24,BAUD9600            ;
CALL initUART               ;

/*
ldi ZH,hi8(gpLabel)         ; obtain the address of the General Purpose Register label
ldi ZL,lo8(gpLabel)         ;
call printStr
*/

.global loop
loop:
RJMP loop


.global TIMER1_OVF_vect
TIMER1_OVF_vect:
INC r17
SBRS r17, 0
RJMP even
LDI r16, 0x86
STS OCR1BH, r16
LDI r16, 0x1B
STS OCR1BL, r16
RJMP end
even:
LDI r16, 0x97
STS OCR1BH, r16
LDI r16, 0xAB
STS OCR1BL, r16
end:
CALL delay
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
