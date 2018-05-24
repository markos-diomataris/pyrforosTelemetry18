/*
   emulate piccolo: about every 100 ms set a pin to HIGH and send 2 bytes
*/
#include<SoftwareSerial.h>

#define INTERRUPT_PIN 3

SoftwareSerial Serial_piccolo(10 /*RX*/, 11 /*TX*/);

void setup() {
  Serial.begin(9600);
  Serial_piccolo.begin(115200);
  pinMode(INTERRUPT_PIN, OUTPUT);
  digitalWrite(INTERRUPT_PIN, LOW);
}

uint8_t c = 0x18, d = 0x19;

void loop() {
  digitalWrite(INTERRUPT_PIN,HIGH);
  delay(1);
  Serial_piccolo.write(c++);
  Serial_piccolo.write(d++);
  digitalWrite(INTERRUPT_PIN,LOW);
  delay(100);


}
