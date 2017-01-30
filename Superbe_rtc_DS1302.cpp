/*
	Superbe_rtcDS1302.cpp - Library for using DS1302 RTC
	Created by Gael from superbe.be, 26/01/17
*/

#include "Arduino.h"
#include "Superbe_rtc_DS1302.h"

Rtc_DS1302::Rtc_DS1302() {
}

void Rtc_DS1302::begin(int clkPin, int dataPin, int cePin) {
	_ClkPin = clkPin;
	_DataPin = dataPin;
	_CePin = cePin;
	pinMode(_ClkPin, OUTPUT);
	digitalWrite(_ClkPin, LOW);
	pinMode(_CePin, OUTPUT);
	digitalWrite(_CePin, LOW);
}

void Rtc_DS1302::readTime() {
	digitalWrite(_CePin, HIGH);
	pinMode(_DataPin, OUTPUT);
	_envoyerByteSaufClock(CLOCK_BURST_READ);
	pinMode(_DataPin, INPUT);
	digitalWrite(_ClkPin, LOW);
	second = _bcdToDec(_recevoirByte());
	minute = _bcdToDec(_recevoirByte());
	hour = _bcdToDec(_recevoirByte());
	digitalWrite(_CePin, LOW);
}

void Rtc_DS1302::readDateTime() {
	digitalWrite(_CePin, HIGH);
	pinMode(_DataPin, OUTPUT);
	_envoyerByteSaufClock(CLOCK_BURST_READ);
	pinMode(_DataPin, INPUT);
	digitalWrite(_ClkPin, LOW);
	second = _bcdToDec(_recevoirByte());
	minute = _bcdToDec(_recevoirByte());
	hour = _bcdToDec(_recevoirByte());
	monthDay = _bcdToDec(_recevoirByte());
	month = _bcdToDec(_recevoirByte());
	weekDay = _bcdToDec(_recevoirByte());
	year = _bcdToDec(_recevoirByte());
	digitalWrite(_CePin, LOW);
}

void Rtc_DS1302::writeTime(int _hour, int _minute, int _second) {
	_writeRegister(CONTROL_ADDRESS_WRITE, 0x00);
	_writeRegister(SECONDS_ADDRESS_WRITE, _decToBcd(_second));
	_writeRegister(MINUTES_ADDRESS_WRITE, _decToBcd(_minute));
	_writeRegister(HOUR_ADDRESS_WRITE, _decToBcd(_hour));
	_writeRegister(CONTROL_ADDRESS_WRITE, 0x80);
}

void Rtc_DS1302::writeDateTime(int _year, int _month, int _monthDay, int _weekDay, int _hour, int _minute, int _second) {
	_writeRegister(CONTROL_ADDRESS_WRITE, 0x00);
	digitalWrite(_CePin, HIGH);
	pinMode(_DataPin, OUTPUT);
	_envoyerByte(CLOCK_BURST_WRITE);
	_envoyerByte(_decToBcd(_second));
	_envoyerByte(_decToBcd(_minute));
	_envoyerByte(_decToBcd(_hour));
	_envoyerByte(_decToBcd(_monthDay));
	_envoyerByte(_decToBcd(_month));
	_envoyerByte(_decToBcd(_weekDay));
	_envoyerByte(_decToBcd(_year));
	_envoyerByte(0x80);
	digitalWrite(_CePin, LOW);
}

byte Rtc_DS1302::_bcdToDec(byte val) {
	return ((val/16*10) + (val%16));
}

byte Rtc_DS1302::_decToBcd(byte val) {
	return ((val/10*16) + (val%10));
}

byte Rtc_DS1302::_readRegister(byte address) {
	digitalWrite(_CePin, HIGH);
	pinMode(_DataPin, OUTPUT);
	_envoyerByteSaufClock(address);
	pinMode(_DataPin, INPUT);
	digitalWrite(_ClkPin, LOW);
	byte x = _recevoirByteSaufClock();
	digitalWrite(_CePin, LOW);
	return x;
}

void Rtc_DS1302::_writeRegister(byte address, byte data) {
	digitalWrite(_CePin, HIGH);
	pinMode(_DataPin, OUTPUT);
	_envoyerByte(address);
	_envoyerByte(data);
	digitalWrite(_CePin, LOW);
}

void Rtc_DS1302::_envoyerByte(byte x) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(_DataPin, bitRead(x, i));
    digitalWrite(_ClkPin, HIGH);
    digitalWrite(_ClkPin, LOW);
  }
}

void Rtc_DS1302::_envoyerByteSaufClock(byte x) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(_DataPin, bitRead(x, i));
    digitalWrite(_ClkPin, HIGH);
    if (i < 7) digitalWrite(_ClkPin, LOW);
  }
}

byte Rtc_DS1302::_recevoirByte() {
  byte x = 0;
  for (int i = 0; i < 8; i++) {
    bitWrite(x, i, digitalRead(_DataPin));
    digitalWrite(_ClkPin, HIGH);
    digitalWrite(_ClkPin, LOW);
  }
  return x;
}

byte Rtc_DS1302::_recevoirByteSaufClock() {
  byte x = 0;
  for (int i = 0; i < 8; i++) {
    bitWrite(x, i, digitalRead(_DataPin));
    if (i < 7) digitalWrite(_ClkPin, HIGH);
    if (i < 7) digitalWrite(_ClkPin, LOW);
  }
  return x;
}