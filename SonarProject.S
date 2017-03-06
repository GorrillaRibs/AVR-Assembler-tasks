#include "avr/io.h"

.global setup
setup:
cli
clr r17
sbi _SFR_IO_ADDR(DDRB), DDB2
ldi r16, (1<<COM1B1)|(1<<COM1B0)|(1<<WGM11)
sts TCCR1A, r16
ldi r16, (1<<CS11)|(1<<WGM13)|(1<<WGM12)
sts TCCR1B, r16
ldi r16, 0x9C
sts ICR1H, r16
ldi r16, 0x3F
sts ICR1L, r16
ldi r16, 0x98
sts OCR1BH, r16
ldi r16, 0xBB
sts OCR1BL, r16
ldi r16, (1<<TOIE1)            
sts TIMSK1,r16                 
sei
ret

.global loop
loop:
rjmp loop

.global TIMER1_OVF_vect 
TIMER1_OVF_vect:
inc r17
sbrs r17, 0
rjmp even
ldi r16, 0x86
sts OCR1BH, r16
ldi r16, 0x1B
sts OCR1BL, r16
rjmp end
even:
ldi r16, 0x97
sts OCR1BH, r16
ldi r16, 0xAB
sts OCR1BL, r16
end:
call delay
reti

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
