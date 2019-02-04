/*
	ds3231.h
*/
#ifndef DS3231_h
#define DS3231_h

#include "Arduino.h"



// Use TinyWireM for ATtiny variants, otherwise use Wire
#if defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__)
	#include <TinyWireM.h>
#else
	#include <Wire.h>
#endif



#define DS3231_I2C_ADDRESS 0x68



class DS3231 {
	private:
		byte _second;
		byte _minute;
		byte _hour;
		byte _day_of_week;
		byte _day_of_month;
		byte _month;
		byte _year;

		
		byte _bcd_to_dec(byte _val);
		byte _dec_to_bcd(byte _val);

		String _get_day_of_week_string(byte _day_of_week);


	public:
		DS3231();

		void set_time(int _second,int _minute,int _hour,int _day_of_week,int _day_of_month,int _month,int _year);

		void get_time();

		void display_time();

		byte get_second();
		byte get_minute();
		byte get_hour();
		byte get_day_of_week();
		byte get_day_of_month();
		byte get_month();
		byte get_year();
};

#endif