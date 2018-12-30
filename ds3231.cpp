#include "DS3231.h"
#include "Arduino.h"



DS3231::DS3231() {

	#if defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__)
		TinyWireM.begin();
	#else
		Wire.begin();
	#endif
}



void DS3231::set_DS3231_time(int _second, int _minute, int _hour, int _day_of_week, int _day_of_month, int _month, int _year) {
	#if defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__)
		// sets time and date data to DS3231
		TinyWireM.beginTransmission(DS3231_I2C_ADDRESS);
		TinyWireM.write(0); // set next input to start at the seconds register
		TinyWireM.write(_dec_to_bcd(_second)); // set seconds
		TinyWireM.write(_dec_to_bcd(_minute)); // set minutes
		TinyWireM.write(_dec_to_bcd(_hour)); // set hours
		TinyWireM.write(_dec_to_bcd(_day_of_week)); // set day of week (1=Sunday, 7=Saturday)
		TinyWireM.write(_dec_to_bcd(_day_of_month)); // set date (1 to 31)
		TinyWireM.write(_dec_to_bcd(_month)); // set month
		TinyWireM.write(_dec_to_bcd(_year)); // set year (0 to 99)
		TinyWireM.endTransmission();
	#else
		// sets time and date data to DS3231
		Wire.beginTransmission(DS3231_I2C_ADDRESS);
		Wire.write(0); // set next input to start at the seconds register
		Wire.write(_dec_to_bcd(_second)); // set seconds
		Wire.write(_dec_to_bcd(_minute)); // set minutes
		Wire.write(_dec_to_bcd(_hour)); // set hours
		Wire.write(_dec_to_bcd(_day_of_week)); // set day of week (1=Sunday, 7=Saturday)
		Wire.write(_dec_to_bcd(_day_of_month)); // set date (1 to 31)
		Wire.write(_dec_to_bcd(_month)); // set month
		Wire.write(_dec_to_bcd(_year)); // set year (0 to 99)
		Wire.endTransmission();
	#endif
}



byte DS3231::_bcd_to_dec(byte _val) {
	return( (_val/16*10) + (_val%16) );
}



byte DS3231::_dec_to_bcd(byte _val) {
	return( (_val/10*16) + (_val%10) );
}



void DS3231::get_DS3231_time() {
	#if defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__)
		TinyWireM.beginTransmission(DS3231_I2C_ADDRESS);
		TinyWireM.send(0); // set DS3231 register pointer to 00h
		TinyWireM.endTransmission();
		TinyWireM.requestFrom(DS3231_I2C_ADDRESS, 7);
		// request seven bytes of data from DS3231 starting from register 00h
		this->_second = _bcd_to_dec(TinyWireM.receive() & 0x7f);
		this->_minute = _bcd_to_dec(TinyWireM.receive());
		this->_hour = _bcd_to_dec(TinyWireM.receive() & 0x3f);
		this->_day_of_week = _bcd_to_dec(TinyWireM.receive());
		this->_day_of_month = _bcd_to_dec(TinyWireM.receive());
		this->_month = _bcd_to_dec(TinyWireM.receive());
		this->_year = _bcd_to_dec(TinyWireM.receive());
	#else
		Wire.beginTransmission(DS3231_I2C_ADDRESS);
		Wire.write(0); // set DS3231 register pointer to 00h
		Wire.endTransmission();
		Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
		// request seven bytes of data from DS3231 starting from register 00h
		this->_second = _bcd_to_dec(Wire.read() & 0x7f);
		this->_minute = _bcd_to_dec(Wire.read());
		this->_hour = _bcd_to_dec(Wire.read() & 0x3f);
		this->_day_of_week = _bcd_to_dec(Wire.read());
		this->_day_of_month = _bcd_to_dec(Wire.read());
		this->_month = _bcd_to_dec(Wire.read());
		this->_year = _bcd_to_dec(Wire.read());
	#endif

}



String DS3231::_get_day_of_week_string(byte _day_of_week) {
	switch(_day_of_week){
		case 1:
			return "Sunday"; break;
		case 2:
			return "Monday"; break;
		case 3:
			return "Tuesday"; break;
		case 4:
			return "Wednesday"; break;
		case 5:
			return "Thursday"; break;
		case 6:
			return "Friday"; break;
		case 7:
			return "Saturday"; break;
  }
}



void DS3231::display_time() {
	// retrieve data from DS3231
	get_DS3231_time();

	Serial.print(get_hour(), DEC);

	// convert the byte variable to a decimal number when displayed
	Serial.print(":");

	if (get_minute()<10)
	Serial.print("0");

	Serial.print(get_minute(), DEC);
	Serial.print(":");

	if (get_second()<10)
	Serial.print("0");

	Serial.print(get_second(), DEC);
	Serial.print(" ");
	Serial.print(get_month(), DEC);
	Serial.print("/");
	Serial.print(get_day_of_month(), DEC);
	Serial.print("/");
	Serial.print(get_year(), DEC);
	Serial.print(" Day of week: ");

	Serial.println(_get_day_of_week_string(get_day_of_week())); 
}



byte DS3231::get_second() {
	return this->_second;
}



byte DS3231::get_minute() {
	return this->_minute;
}



byte DS3231::get_hour() {
	return this->_hour;
}



byte DS3231::get_day_of_week() {
	return this->_day_of_week;
}



byte DS3231::get_day_of_month() {
	return this->_day_of_month;
}



byte DS3231::get_month() {
	return this->_month;
}



byte DS3231::get_year() {
	return this->_year;
}