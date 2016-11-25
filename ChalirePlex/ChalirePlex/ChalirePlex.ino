#include <Arduino.h>

/*
   CharliePlex.ino
   Purpose: To learn how to drive multiple LEDs from
         less I/O pins on an ATTiny85
   Code by Robert Raffaele "GorrillaRibs" Miller
   ACES 2016/17
   STATUS: It probably works but hey I can't wire properly

   LED things
   first - 2 low 3 high
   Second - 3 high 2 low
   third - 5 high 3 low
   fourth - 3 high 5 low
   fifth - 2 high 5 low
   sixth - 5 high 2 high

 */

 uint8_t port[] = {0b00000010, 0b00000100, 0b00000001, 0b00000010, 0b00000001, 0b00000100};
 uint8_t DDR[] = {0b0000110, 0b00000110, 0b00000011, 0b00000011, 0b00000101, 0b00000101};
 uint8_t count = sizeof(DDR);

void setup() {
        asm (
                "luup: \n"
                "LDI r26, lo8(port) \n"
                "LDI r27, hi8(port) \n"
                "LDI r30, lo8(DDR) \n"
                "LDI r31, hi8(DDR) \n"
                "LDS r2, count \n"

                "luuup: \n"
                "LD r16, Z+ \n"
                "OUT 0x17, r16 \n"
                "LD r16, X+ \n"
                "OUT 0x18, r16 \n"
                "RCALL delay \n"
                "DEC R17 \n"
                "BRNE luuup \n"
                "RJMP luup \n"

                "delay: \n" // delay, 200ms
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
