#include <ds3231.h>

// #define DEBUG 1

#define BAUDRATE 9600

// Seconds offset to make up for uploading time
#define SECONDS_OFFSET 6

// Create DS3231 object
DS3231 rtc;



void setup() {
	Serial.begin(BAUDRATE);

	int _second,_minute,_hour,_day_of_week,_day_of_month,_month,_year;

	// Get the time in integer form from the compile time of the script
	get_time(__TIME__,_second,_minute,_hour);

	// Get the date in integer form from the compile date of the script
	get_date(__DATE__,_day_of_week,_day_of_month,_month,_year);


	#ifdef DEBUG
		Serial.println(_second);
		Serial.println(_minute);
		Serial.println(_hour);

		Serial.println(_day_of_week);
		Serial.println(_month);
		Serial.println(_day_of_month);
		Serial.println(_year);
	#endif

	// Instantiate RTC object
	rtc = DS3231();

	if( (_second + SECONDS_OFFSET) >= 60) {
		_second -= 60;
		_minute++;
	}

	// Set the time of the DS3231 RTC
	rtc.set_time(_second,_minute,_hour,_day_of_week,_day_of_month,_month,_year);
}



void loop() {
	// Retrieve the time from the RTC
	rtc.get_time();

	// Print the RTC time
	rtc.print_time();
}



// Converts the time (hour, minute, and second) from String to integer
void get_time(String _time,int & _second,int & _minute, int & _hour) {
	#ifdef DEBUG
		Serial.println(_time);
	#endif

	int delimiter1 = _time.indexOf(':');
	int delimiter2 = _time.indexOf(':',delimiter1+1);

	_hour = _time.substring(0,delimiter1).toInt();
	_minute = _time.substring(delimiter1+1,delimiter2).toInt();
	_second = _time.substring(delimiter2+1).toInt();

	#ifdef DEBUG
		Serial.println(_hour);
		Serial.println(_minute);
		Serial.println(_second);
	#endif
}



// Converts the date (day of week, day of month, month, and year) from String to integer
void get_date(String _date,int & _day_of_week,int & _day_of_month,int & _month,int & _year) {
	Serial.println(_date);

	String _month_str;

	int delimiter1 = _date.indexOf(' ');
	int delimiter2 = _date.indexOf(' ',delimiter1+1);

	_month_str = _date.substring(0,delimiter1);
	_day_of_month = _date.substring(delimiter1+1,delimiter2).toInt();
	_year = _date.substring(delimiter2+1).toInt();

	_month = get_month(_month_str);
	if(_month == -1)
		Serial.println("ERROR DETERMINING MONTH...");
	_day_of_week = get_day_of_week(_day_of_month,_month,_year);

	_year -= 2000;
	
	Serial.println(_day_of_week);
	Serial.println(_day_of_month);
//  Serial.println(_month);
//  Serial.println(_year);
}



// Determine day of the week based on the day of the month, month, and year
int get_day_of_week(int day_of_month,int month,int year) {
	int key_value = get_key_value(month);
	int leap_year_offset = get_leap_year_offset(year);
	int century_code = get_century_code(year);

	int day_of_week = (((year % 100) / 4 + day_of_month) + key_value - leap_year_offset + century_code + (year % 100)) % 7;

	Serial.println(key_value);
	Serial.println(leap_year_offset);
	Serial.println(century_code);
	Serial.println(day_of_week);

	if(day_of_week == 0)
		return 7;
	else
		return day_of_week;
}



// Determine century code based on year
int get_century_code(int year) {
	Serial.println(year);
	if(year >= 2000)
		return 6;
	else if(year >= 1900)
		return 0;
	else if(year >= 1800)
		return 2;
	else
		return 4;
}



// Determines offset based on current year
int get_leap_year_offset(int year) {
	if(year % 400 == 0) {
		switch(year) {
			case(1):
			case(2):
				return 1;
			default:
				return 0;
		}
	}
	else
		return 0;
}



// Get Key Value
int get_key_value(int month) {
	switch(month) {
		case(1):
			return 1;
		case(2):
		 return 4;
		case(3):
		 return 4;
		case(4):
		 return 0;
		case(5):
		 return 2;
		case(6):
		 return 5;
		case(7):
		 return 0;
		case(8):
		 return 3;
		case(9):
		 return 6;
		case(10):
		 return 1;
		case(11):
		 return 4;
		case(12):
		 return 6;
	}
}



// Converts the month String to an integer
int get_month(String str) {
	if(str == "Jan")
		return  1;
	else if(str == "Feb")
		return  2;
	else if(str == "Mar")
		return  3;
	else if(str == "Apr")
		return  4;
	else if(str == "May")
		return  5;
	else if(str == "Jun")
		return  6;
	else if(str == "Jul")
		return  7;
	else if(str == "Aug")
		return  8;
	else if(str == "Sep")
		return  9;
	else if(str == "Oct")
		return 10;
	else if(str == "Nov")
		return 11;
	else if(str == "Dec")
		return 12;
	else
		return -1;
}
