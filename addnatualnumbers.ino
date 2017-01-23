uint8_t n = 8;

void setup() {
Serial.begin(9600);
Serial.println("sum o da first whatever natural nubers is");

}

void loop() {



}

uint16_t sum (uint8_t n) {

if (n==1) return 1;

return n+sum(n-1);

}
