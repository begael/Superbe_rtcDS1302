#include <Superbe_rtc_DS1302.h>

const int rtc_CLK = 6;
const int rtc_DATA = 7;
const int rtc_CE = 8;

Rtc_DS1302 rtc;

void setup() {
  Serial.begin(9600);
  rtc.begin(rtc_CLK, rtc_DATA, rtc_CE);
  rtc.writeTime(23, 28, 30);
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
