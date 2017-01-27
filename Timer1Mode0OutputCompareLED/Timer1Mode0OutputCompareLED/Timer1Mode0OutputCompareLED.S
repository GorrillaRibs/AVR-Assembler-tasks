
;  Timer1Mode0OutputCompareLED.ino
;  Purpose: to flash an LED at 0.5Hz exactly using timers and
;         hardware interupts
;  Code by: Robert Raffaele "GorrillaRibs" Miller


#include "avr/io.h"

.global setup
setup:
SBI _SFR_IO_ADDR(DDRB), DDB1
LDI r16, 1 << COM1A0
; Timer setup starts
STS TCCR1A, r16
STS TCNT1H, r16  ; high byte
STS TCNT1L, r16  ; low byte
LDI r16, 0x04
STS TCCR1B, r16  ; load a prescaler
LDI r16, 1 << TOIE1
STS TIMSK1, r16
; Timer setup ends
LDI r16, 0xFF
; No less than 7 sacrifices to Cthulu required to function
STS OCR1AH, r16  ; high byte
LDI r16, 0xFF
STS OCR1AL, r16  ; low byte

SEI ; Turn interupts on


.global loop
loop:
RJMP loop
