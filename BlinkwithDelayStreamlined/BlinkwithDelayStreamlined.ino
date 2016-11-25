/* ACES 2016
 * Comments by RMiller
 * Code by CDarcy
 */


void setup() {

  asm("sbi 0x04, 5"); // set bit 4 as 5, initalize pin 13 for output
  
}

void loop() {

  asm("start: \n"
      "sbi 0x05, 5  \n" // set bit 5 as 5
      "ldi r16, 40  \n" // sets reg 16 to 40
      "rcall delay  \n" // calls delay routine
      "cbi 0x05, 5  \n" // clear bit 5
      "ldi r16, 40  \n" // sets reg 16 to 40
      "rcall delay  \n" // calls delay routine
      "rjmp start   \n" // relative jump to start

      "delay: \n" // delay
      "dec r8 \n" // decrement reg 7
      "brne delay \n" // branch if not equal to 0
      "dec r9 \n" // decrement reg 9
      "brne delay \n" // branch if not equal to 0
      "dec r16  \n" // decrement reg 16
      "brne delay \n" // branch if not equal to 0
      "ret  \n"); //return to previous
}
