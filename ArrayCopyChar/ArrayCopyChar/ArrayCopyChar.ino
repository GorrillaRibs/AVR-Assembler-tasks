#include <Arduino.h>

/*
   ArrayCopyChar.ino
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17
 */

char inText[] = "ACES";
char outText [] = "    ";

void setup() {

        Serial.begin(9600);
        Serial.print("The duplicate of " + String(inText) + " is ");

        asm ( "start: \n"
              "LDI r26, lo8(inText) \n"
              "LDI r27, hi8(inText) \n"
              "LDI r30, lo8(outText) \n"
              "LDI r31, hi8(outText) \n"
              "luup: \n"
              "LD r14, X+ \n"
              "ST Z+, r14 \n"
              "CP r14, 0x00 \n"
              "BREQ end \n"
              "JMP luup \n"

              "end: \n"
              "nop \n"

              );

Serial.print(outText);

}

void loop() {
}
