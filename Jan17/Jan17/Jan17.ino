#include <Arduino.h>

void setup(){
  Serial.begin(9600);
    pinMode(11,OUTPUT);
    digitalWrite(11, HIGH);

}
void loop() {

   for (int i=0; i<1024; i++) {
        Serial.println(i);
         analogWrite(11,i);
         delay(30);
   }

}
