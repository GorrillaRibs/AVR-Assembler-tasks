

void setup() {
  
  asm("sbi 0x0A,0x05"); // pinMode(4, OUTPUT)

}

void loop() {
  
  asm("sbi 0x0B,0x04"); // digitalWrite(4, HIGH);
  delay(1000);
  asm("cbi 0x0B,0x04"); // digitalWrite(4, LOW);
  delay(1000);

}
