/*
	Superbe_rtc_DS1302.h - Library for using DS1302 RTC
	Created by Gael from superbe.be, 26/01/2017
*/

#ifndef Superbe_rtc_DS1302_h
#define Superbe_rtc_DS1302_h

#define CONTROL_ADDRESS_WRITE 0x8E
#define CLOCK_BURST_READ 0xBF
#define CLOCK_BURST_WRITE 0xBE
#define SECONDS_ADDRESS_WRITE 0x80
#define MINUTES_ADDRESS_WRITE 0x82
#define HOUR_ADDRESS_WRITE 0x84

#include "Arduino.h"

class Rtc_DS1302 {
	public:
		Rtc_DS1302();
		void begin(int clkPin, int dataPin, int cePin);
		void readTime();
		void readDateTime();
		void writeTime(int _hour, int _minute, int _second);
		void writeDateTime(int _year, int _month, int _monthDay, int _weekDay, int _hour, int _minute, int _second);
		int second;
		int minute;
		int hour;
		int weekDay;
		int monthDay;
		int month;
		int year;		
	private:
		void _writeRegister(byte address, byte data);
		byte _readRegister(byte address);
		byte _bcdToDec(byte val);
		byte _decToBcd(byte val);
		int _ClkPin;
		int _DataPin;
		int _CePin;
		void _envoyerByte(byte x);
		void _envoyerByteSaufClock(byte x);
		byte _recevoirByte();
		byte _recevoirByteSaufClock();
};

#endif