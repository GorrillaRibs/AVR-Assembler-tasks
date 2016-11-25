void setup() {
  // put your setup code here, to run once:
  asm("sbi 0x04, 5");
}

void loop() {
  // put your main code here, to run repeatedly:
  asm("start:");
  asm("sbi 0x05, 5");
  asm("ldi r16, 0x20");
  asm("rcall delay");
  asm("cbi 0x05, 5");
  asm("ldi r16, 0x20");
  asm("rcall delay");
  asm("rjmp start");

  asm("delay:");
  asm("dec r8");
  asm("brne delay");
  asm("dec r9");
  asm("brne delay");
  asm("dec r16");
  asm("brne delay");
  asm("ret");

}
