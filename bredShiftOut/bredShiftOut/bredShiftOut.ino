#include <Arduino.h>

//SHIFTOUT

uint8_t value = 0x55;

void setup() {
  // latchPin = 3
  // clockPin = 2
  // dataPin  = 4
  // r7, data clone for shifting out lowest bit
  // r8, empty register
  // r9, loop counter
  asm(
    "LDI r24, 0xFF  \n" //
    "out 0x0A, r24  \n" // Set pins 0-7 to OUTPUT
    "cbi 0x0B, 0x03 \n" // Set latch pin low
    "clr r8         \n" // Use r8 for empty comparator
    "lds r6, value  \n" // Use r6 as data we shift out
    "ldi r24, 0x08  \n" // loop count
    "mov r9, r24    \n"
    "ldi r24, 0x80  \n" // AND mask
    "mov r10, r24   \n"

    "shifting:      \n"
      "cbi 0x0B, 0x02 \n" // Clock pin low
      "mov r7, r6     \n" // Clone data for destructive use
      "and r7, r10    \n" // SET Z if zero, else CLR Z
      "breq notZero   \n" //
      "sbi 0x0B, 0x04 \n" // Set data high if LSB is low
      "jmp equalDone  \n" //
      "notZero:       \n" //
      "cbi 0x0B, 0x04 \n" //
      "equalDone:     \n" //
      "sbi 0x0B, 0x02 \n" // Clock pin high
      "lsr r10        \n"
    "brne shifting \n"
    "sbi 0x0B, 0x03\n" // set latch back to high
    );
}

void loop() {}
