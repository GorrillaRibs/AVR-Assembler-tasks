#include <Arduino.h>

/*
   Swapping3.ino
   code by: Robert Raffaele "GorrillaRibs" Miller
   It's a thing
 */

uint8_t data = 0xF0;

void setup() {
        Serial.begin(9600);
        asm (
                "LDS r20, data \n"
                "swap r16 \n"
                "STS data, r20 \n"

                );


        Serial.println(data);

}

void loop() {
}
