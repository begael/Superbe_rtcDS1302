#include <Superbe_rtc_DS1302.h>

const int rtc_CLK = 6;
const int rtc_DATA = 7;
const int rtc_CE = 8;

Rtc_DS1302 rtc;

void setup() {
  Serial.begin(9600);
  rtc.begin(rtc_CLK, rtc_DATA, rtc_CE);
  rtc.writeDateTime(15, 2, 23, 1, 23, 28, 30);	//!!! pas 2015 !!!
}

void loop() {
  rtc.readDateTime();
  Serial.print(rtc.weekDay);
  Serial.print(",");
  Serial.print(rtc.monthDay);
  Serial.print("/");
  Serial.print(rtc.month);
  Serial.print("/");
  Serial.print(rtc.year);
  Serial.print(" ");
  Serial.print(rtc.hour);
  Serial.print(":");
  Serial.print(rtc.minute);
  Serial.print(":");
  Serial.println(rtc.second);
  delay(1000);
}
