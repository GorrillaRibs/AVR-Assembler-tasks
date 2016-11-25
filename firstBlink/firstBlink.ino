

void setup() {
  
  asm("sbi 0x04,0x05"); // pinMode(13, OUTPUT)

}

void loop() {
  
  asm("sbi 0x05,0x05"); // digitalWrite(13, HIGH);
  delay(1000);
  asm("cbi 0x05,0x05"); // digitalWrite(13, LOW(;
  delay(1000);

}
