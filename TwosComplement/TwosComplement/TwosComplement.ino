#include <Arduino.h>
/*
TwosComplement.ino
Purpose - To find the Two's complement of a byte value
Robert Raffaele 'GorrillaRibs' Miller
ACES 2016/17
*/

byte value = 23;

void setup() {
  Serial.begin(9600);
  Serial.println("the negative of");
  Serial.print(value);
  Serial.print(" is");
  Serial.println();
  asm("lds r31, value \n"
  "com r31 \n"
  "inc r31 \n"
  "sts value, r31");
  delay(300);
  Serial.print(value);

}

void loop() {


}
