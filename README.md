# Superbe_rtcDS1302
Arduino Library for the RTC DS1302

Available :

Rtc_DS1302();
void begin(int clkPin, int dataPin, int cePin);
void readTime();
void readDateTime();
void writeTime(int _hour, int _minute, int _second);
void writeDateTime(int _year, int _month, int _monthDay, int _weekDay, int _hour, int _minute, int _second); //year 0-99 !!!
int second;
int minute;
int hour;
int weekDay;
int monthDay;
int month;
int year;
