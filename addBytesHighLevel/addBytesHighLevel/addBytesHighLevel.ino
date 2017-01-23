#include <Arduino.h>
// .include "m16def.inc" // how do dis

uint8_t OPA = 0xCC;            // Addition: augend
uint8_t OPB = 0xCD;            // Addition: addend
uint8_t sum;
// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);       // prepare output to Serial Monitor
//   Serial.print(opA);
//   Serial.print('+');
//   Serial.print(opB);
//   Serial.print('=');
//   int sum = add(opA, opB);  // invoke function to obtain sum
//   Serial.println(sum);      // publish result
// }
// // function accepts two byte parameters, returns the int total
// int add(byte a, byte b) {
//   int total = a + b;
//   return total;
// }
// void loop() {}

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  Serial.end();
        asm (
                "LDS r16, OPA \n"
                "LDS r17, OPB \n"
      //          "CLR r20 \n"
        //        "CLR r22 \n"
    //            "PUSH r16 \n"
  //              "PUSH r17 \n"
    //            "RCALL addd \n"
    //            "POP r10 \n"
      //          "POP r11 \n"
                "STS sum, r10 \n"
                "STS sum+1, r11 \n"
    //            "RJMP end \n"

                "addd: \n"/*
                "POP r8 \n"  // SP 1
                "POP r9 \n"  // SP 2
                "POP r19 \n"
                "POP r21 \n"
                "ADD r21, r19 \n"
                "ADC r20, r22 \n"
                "PUSH r20 \n"
                "PUSH r21 \n"
                "PUSH r9 \n"
                "PUSH r8 \n"*/
//                "RET \n"

                "end: \n"
              //  "NOP \n"

                );
                Serial.begin(9600);
Serial.println(sum);

}

void loop() {
}
