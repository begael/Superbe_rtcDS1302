#include <Superbe_rtc_DS1302.h>

#define CLKPIN 6
#define DATAPIN 7
#define CEPIN 8

Rtc_DS1302 rtc;

void setup() {
  rtc.begin(CLKPIN, DATAPIN, CEPIN);
  Serial.begin(9600);
}

void loop() {
  rtc.readTime();
  Serial.print(rtc.hour);
  Serial.print(":");
  Serial.print(rtc.minute);
  Serial.print(":");
  Serial.println(rtc.second);
  delay(1000);
}
