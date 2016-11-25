#include <Arduino.h>

uint8_t data = 0;
uint8_t highBits = 0;

//We can bitshift and analize one bit
//or keep constant and change bit read

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  data = random(0,256);
  Serial.print("\nValue of data is " + String(data,BIN));
  //Use r16 as data byte, use r17 as high bit count,
  //use r2 as arithmetic register
  delay(1000);
  asm(
  "lds r16,data \n"
  "clc \n"        //Clear carry bit
  "ror r16 \n"     //rotate b0 -> C
  "rcall setcheck \n"
  "ror r16 \n"     //rotate b0 -> b7
  "rcall setcheck \n"
  "ror r16 \n"     //rotate b0 -> b6
  "rcall setcheck \n"
  "ror r16 \n"     //rotate b0 -> b5
  "rcall setcheck \n"
  "ror r16 \n"     //rotate b0 -> b4
  "rcall setcheck \n"
  "ror r16 \n"     //rotate b0 -> b3
  "rcall setcheck \n"
  "ror r16 \n"     //rotate b0 -> b2
  "rcall setcheck \n"
  "ror r16 \n"     //rotate b0 -> b1
    "rcall setcheck \n"
    "ror r16 \n"     //rotate b0 -> b0 : r16 = data again
    "rcall setcheck \n"
    "rjmp done \n"
    "setcheck: \n"
    "clr r2 \n"
    "bst r16,0 \n"
    "bld r2,0 \n"
  //  "add r17,r2 \n"//<-Comment and uncomment
    "ret \n"
    "done: \n"
    /*"andi r17,0x01 \n"
    "subi r17,1 \n"
    "BRNE end \n"  //If odd, use BRNE if odd parity, use BREQ if odd parity
    "ori r16,0x80 \n"
    "end: \n"*/
    "sts data,r16 \n"
    "sts highBits,r17 \n"
    );
    Serial.print(" the parity of it is " + String(data,BIN));
    Serial.print(". The number of high bits is " + String(highBits));
  }

  void loop() {}
