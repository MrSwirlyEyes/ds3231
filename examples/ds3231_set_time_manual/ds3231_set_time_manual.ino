#include <DS3231.h>
//This program programs the Real Time Clock (RTC) DS3231

DS3231 rtc = DS3231();

char c;
String str = "";

int _year;
int _month;
int _day_of_month;
int _day_of_week;
int _hour;
int _minute;
int _second;

void setup() {   

	Serial.begin(9600);
	
	print_intro_message();
	
	set_time();
	
	print_outro_message();
}

void loop() {

	rtc.display_time(); // display the real-time clock data on the Serial Monitor,  
	delay(100); // every second
}

int get_time(String field, int num_digits, int min_range, int max_range) {
	do {
		str = "";
		Serial.print("Please enter the ");
		field.toUpperCase();
		Serial.print(field);
		field.toLowerCase();
		Serial.println(": ");
		
		Serial.print("    Format: ");
		Serial.print(num_digits);
		Serial.print(" digit number between ");
		Serial.print(min_range);
		Serial.print("-");
		Serial.println(max_range);

		if (field == "day of week") {
				Serial.println("    +---------------------+");
				Serial.println("    | Day of Week | Value |");
				Serial.println("    |-------------|-------|");
				Serial.println("    |  Sunday     |   1   |");
				Serial.println("    |  Monday     |   2   |");
				Serial.println("    |  Tuesday    |   3   |");
				Serial.println("    |  Wednesday  |   4   |");
				Serial.println("    |  Thursday   |   5   |");
				Serial.println("    |  Friday     |   6   |");
				Serial.println("    |  Saturday   |   7   |");
				Serial.println("    +---------------------+");
				
		}
		if (field == "month" || field == "day of month" || field == "hour"|| field == "minute" || field == "second") {
				Serial.print("        Note: You need the leading '0' if ");
				Serial.print(field);
				Serial.println(" is less than 10");
		}
		if (field == "second") {
				Serial.println("WARNING: THE RTC DS3231 WILL BE PROGRAMMED");
				Serial.println("             IMMEDIATELY AFTER PRESSING ENTER");
		}

		Serial.println();
		Serial.print("> ");
		
		for (int i = 0 ; i < num_digits ; i++ ) {
			while (Serial.available() == 0) {}
			c = Serial.read();
			Serial.print(c);
			str += c;        
		}

		Serial.println();
		Serial.print("You entered: ");
		Serial.println(str.toInt());

		if (is_valid_time(str, min_range, max_range)) {
			Serial.println();
			return str.toInt();
		} else {
			Serial.println("That was invalid input!");
			Serial.println("Please try again...");            
			Serial.println();
		}                
	} while (!is_valid_time(str, min_range, max_range)); 
}



void set_time() {
	_year = get_time("year", 4, 2000, 2099);
	Serial.print("The YEAR entered was: ");
	Serial.println(_year);
	_year -= 2000;
//    Serial.println("    Moving on to MONTH...");
	Serial.println();

	_month = get_time("month", 2, 1, 12);
	Serial.print("The MONTH entered was: ");
	Serial.println(_month);
//    Serial.println("    Moving on to DAY OF MONTH...");
	Serial.println();

	_day_of_month = get_time("day of month", 2, 1, 31);
	Serial.print("The DAY OF MONTH entered was: ");
	Serial.println(_day_of_month);
//    Serial.println("    Moving on to day of DAY OF WEEK...");
	Serial.println();

	_day_of_week = get_time("day of week", 1, 1, 7);
	Serial.print("The DAY OF WEEK entered was: ");
	Serial.println(_day_of_week);
//    Serial.println("    Moving on to HOURS...");
	Serial.println();

	_hour = get_time("hour", 2, 0, 24);
	Serial.print("The HOURS entered was: ");
	Serial.println(_hour);
//    Serial.println("    Moving on to DAY OF MINUTES...");
	Serial.println();
	
	_minute = get_time("minute", 2, 0, 59);
	Serial.print("The MINUTES entered was: ");
	Serial.println(_minute);
//    Serial.println("    Moving on to SECONDS...");
	Serial.println();

	_second = get_time("second", 2, 0, 59);
	Serial.print("The SECONDS entered was: ");
	Serial.println(_second);

	// set the initial time here:
	// NOTE: 24H time
	// DS3231         seconds, minutes, hours, dayOfWeek, date, month, year
	rtc.set_time(_second, _minute, _hour, _day_of_week, _day_of_month, _month, _year);

	Serial.println();
	Serial.println();
	Serial.println();
}



void print_intro_message() {
	Serial.println("RTC DS3231 Semi-Auto Programmer");
	Serial.println("Please enter VALID DATA ONLY...");
	Serial.println("     (AKA... dont give bad input, or try to break it... It was not built for strong error checking)");
	Serial.println("    IF YOU MESS UP, JUST RESTART THE ARDUINO");
	Serial.println();
	Serial.println();
}

void print_outro_message() {

	display_time();    

	Serial.println("PROGRAMMING THE RTC DS3231...");
	Serial.println();
	Serial.println(".....SUCCESSFULLY PROGRAMMED THE RTC DS3231!");
	Serial.println("Displaying the time until program is terminated...");
}

void display_time() {
	Serial.print("Time entered: ");
	Serial.print(_day_of_week); Serial.print(" ");
	Serial.print(_hour); Serial.print(":");
	Serial.print(_minute); Serial.print(":");
	Serial.print(_second); Serial.print(" ");
	Serial.print(_year); Serial.print("-");
	Serial.print(_month); Serial.print("-");
	Serial.print(_day_of_month); Serial.println();
}

bool is_valid_time(String _str, int _min_range, int _max_range) {
int _time = _str.toInt();
if (_time >= _min_range && _time <= _max_range)
	return true;
else
	return false;
}