#include <Arduino.h>
#include <TM1637Display.h>

int t_hour, t_min, t_sec, millisNow, millisPrev;
int minCounterPrev, hourCounterPrev;
bool canAdjMin, canAdjHour; 
TM1637Display tm1637(3,2);
uint8_t data[] = { 0xFf, 0xff, 0xff, 0xff };
uint8_t nums[] = { 0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f };

void setup() {
  // put your setup code here, to run once:
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  t_hour = 0;
  t_min = 0;
  t_sec = 0;
  tm1637.setBrightness(0xff);
  setTime();
  millisNow = millis();
  millisPrev = millis();
  canAdjMin = true;
  canAdjHour = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  //tm1637.setSegments(data);
  if(digitalRead(4)==HIGH&&canAdjMin)
    addTime(false);
  else if(digitalRead(5)==LOW&&canAdjHour)
    addTime(true);
  millisNow = millis();
  if(millisNow - minCounterPrev >= 500)
    canAdjMin = true;
  if(millisNow - hourCounterPrev >= 500)
    canAdjHour = true;
  if(millisNow-millisPrev>=1000)
    tickTime();
  setTime();
}

void setTime() {
  int digit[] = { t_hour/10, t_hour%10, t_min/10, t_min%10};
  for(int i=0; i<4 ; i++) {
    data[i] = nums[digit[i]];
    tm1637.setSegments(data);
  }
}

void addTime(bool isHour) {
  if(isHour) {
    canAdjHour=false;
    hourCounterPrev = millis();
    t_hour++;
    t_hour = t_hour%24;
  }
  else {
    canAdjMin=false;
    minCounterPrev = millis();
    t_min++;
    t_hour += t_min/60;
    t_min = t_min%60;
    t_hour = t_hour%24;
  }
}

void tickTime() {
  millisPrev = millisNow;
  t_sec++;
  t_min+=t_sec/60;
  t_hour+=t_min/60;
  t_sec = t_sec%60;
  t_min=t_min%60;
  t_hour=t_hour%24;
}
