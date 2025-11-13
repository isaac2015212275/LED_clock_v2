#include <Arduino.h>
#include <TM1637Display.h>

TM1637Display tm1637(3,2);
uint8_t data[] = { 0xd2, 0xff, 0xff, 0xff };

void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // put your main code here, to run repeatedly:
  tm1637.setBrightness(0x0f);
  tm1637.setSegments(data);
}
