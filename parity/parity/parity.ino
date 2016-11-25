// Purpose: To demonstrate the concept of Parity
// Link:    http://darcy.rsgc.on.ca/ACES/TEI4M/1617/AssemblyTasks.html#Parity
// Author:  C. D'Arcy
// Date:    2016 10 06
// Status:  Working

uint8_t data;
uint8_t count;

void setup() {
  Serial.begin(9600);         // set the baud rate to agree with serial monitor
  randomSeed(analogRead(0));  // different starting seed each time
  data = random(128);         // [0,127]
  Serial.println("Data:\t" + String(data, BIN));
  asm("start:           \n"   //
      "lds r16,data     \n"   // obtain the subject of the test
      "clr r17          \n"   // zero the bit count
      "ldi r18,8        \n"   // prepare to examine all 7 bits...
      "ldi r19,0x40     \n"   // set the mask to 1000 0000
      "again:           \n"
      "mov r20,r16      \n"   // obtain a fresh copy of the subject
      "and r20,r19      \n"   // apply the mask
      "breq next        \n"   // if the result zero, subject bit was clear
      "inc r17          \n"   // subject bit is set; increase bit count
      "next:            \n"
      "lsr r19          \n"   // shift the mask to the right one bit
      "brne again       \n"   // is there any mask left? if yes, repeat...

      "sts (count), r17 \n"  // record the count in SRAM
      "ror  r17         \n"  // check to see if count was even
      "brcc done        \n"  // if it is, nothing more to do, skip to done
      "ori  r16,0x80    \n"  // odd! set bit 7 by or'ing the data with 128 (0b1000 0000)
      "done:            \n"  //
      "sts  data,r16    \n"  // we have the result
      "out:             \n"  // exit
     );
  Serial.println("Bit Count:" + String(count));
  Serial.println("EVEN parity: " + String(data, BIN));
}

void loop() {}
