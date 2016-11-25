#include <Arduino.h>

/*
   SumSeries.ino
   Robert Raffaele 'GorrillaRibs' Miller
   ACES 2016/17
 */

uint16_t sum;
uint8_t n = 0xFF;

void setup() {
        Serial.begin(9600);
        asm ("LDS r19, n \n"    // load the number of natural numbers
             "CLR r20 \n"       // incrementing with the loop
             "CLR r21 \n"       // sum register 1
             "CLR r22 \n"       // sum register 2
             "CLR r23 \n"       // empty register for carry addition
             "luup: \n"         // loop label, to return to later
             "CP r20, r19 \n"   // compare n with reg 19 -
             "BREQ done \n"     // when reg 19 = n, finish the program.

             "ADD r21, r20 \n"  // add our incrementing reg into our first total reg
             "ADC r22, 23 \n"   // add carry bit into second sum register to take care of overflow
             "INC r20 \n"       // increment r20, which will eventually equal n
             "JMP luup \n"      // jump back to the luup: label

             "done: \n"         // final label
             "STS sum, r21 \n"  // save the first sum reg from r21
             "STS sum+1, r22 \n"// save second sum reg from r22
             "nop \n"           // nope.
             );
        Serial.println("The sum of the first " + String(n) + " natural numbers is " + String(sum) + ".");
        // and finally print the output.
}

void loop(){
}
