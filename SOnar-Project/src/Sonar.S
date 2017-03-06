; RSGC ACES 2017
; Sonar Assembler Project
; By RM, ST, and SA

#include "avr/io.h"
#include <ASCII.h>
#define BAUD9600 103           //(((F_CPU / (BAUDRATE * 16))) - 1)
#define data 65                //ASCII value translates to 'A' or '\A
#define trig PB1
#define echo PB0

;gpLabel:
;.asciz  "32 GP Registers:\n"

; No less than 7 sacrifices to Cthulu required to function
.global setup
setup:
CALL Timer1Setup1

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

/*
.global TIMER1_OVF_vect
TIMER1_OVF_vect:
INC r17
SBRS r17, 0
RJMP even
LDI r16, 0x86
STS OCR1BH, r16 // 34331
LDI r16, 0x1B
STS OCR1BL, r16
RJMP end
even:
LDI r16, 0x97 // 38827
STS OCR1BH, r16
LDI r16, 0xAB
STS OCR1BL, r16
end:
CALL delay
RETI // YETI
*/





.global Timer1Setup1
Timer1Setup1:
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

.global Timer1Setup2
Timer1Setup2:
//setup for normal mode and interupt
LDI r16, 0                    ; prepare for Normal Mode //sets pin to toggle on 9
STS TCCR1A, r16               ; set Normal Mode, now configure the prescaler...
LDI r16, 0b00000011           ; T1:2^24/2^10/2^16 (prescale) > 0.25 ovf/s > 0.125Hz
STS TCCR1B, r16               ; Timer1 clock = system clock / prescale
LDI r16,hi                    ; load TCNT1 (Timer1's 2-byte counter)
STS TCNT1H,r16                ; T1:2^16-(2^24/2^8/120)=64989=0xFDDD->120ovf/s=60Hz
LDI r16,lo                    ; LED flashing at 24Hz does not seem to produce PoV
STS TCNT1L,r16                ; even at 60Hz there appears to be some noticeable flicker
//setup the toggle pin??
LDI r16, 1<<ICIE1 | 1<<TOIE1  //enable the input capture and OVF interupt
STS TIMSK1, r16
RET


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
