#include  <iostream>
#include "time.h"

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(int aHour, int aMinute, int aSecond) {
	hour = aHour;
	minute = aMinute;
	second = aSecond;
}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}

int Time::getSecond() const {
	return second;
}

void Time::setHour(int h) {
	hour = h;
}

void Time::setMinute(int m) {
	minute = m;
}

void Time::setSecond(int s) {
	second = s;
}

void Time::PrintAmPm() {
	
	if (hour < 12) {
		if (minute < 10)
			if (second < 10) {
				std::cout << hour << ":0" << minute << ":0" << second << "AM\n";
			}
			else {
				std::cout << hour << ":0" << minute << ":" << second << "AM\n";
			}
		else if (minute > 10) {
			if (second < 10) {
				std::cout << hour << ":" << minute << ":0" << second << "AM\n";
			}
			else {
				std::cout << hour << ":" << minute << ":" << second << "AM\n";
			}
		}
	}
	else if (hour > 12) {
		hour = hour - 12;
		if (minute < 10)
			if (second < 10) {
				std::cout << hour << ":0" << minute << ":0" << second << "PM\n";
			}
			else {
				std::cout << hour << ":0" << minute << ":" << second << "PM\n";
			}
		else if (minute > 10) {
			if (second < 10) {
				std::cout << hour << ":" << minute << ":0" << second << "PM\n";
			}
			else {
				std::cout << hour << ":" << minute << ":" << second << "PM\n";
			}
		}
	}
	else {
		if (minute < 10)
			if (second < 10) {
				std::cout << hour << ":0" << minute << ":0" << second << "PM\n";
			}
			else {
				std::cout << hour << ":0" << minute << ":" << second << "PM\n";
			}
		else if (minute > 10) {
			if (second < 10) {
				std::cout << hour << ":" << minute << ":0" << second << "PM\n";
			}
			else {
				std::cout << hour << ":" << minute << ":" << second << "PM\n";
			}
		}
	}

}

bool IsEarlierThan(const Time& t1, const Time& t2) {

	if (t1.getHour() < t2.getHour()) {
		return true;
	}
	else if (t1.getHour() == t2.getHour()) {

		if (t1.getMinute() < t2.getMinute()) {
			return true;

		}
		else if (t1.getMinute() == t2.getMinute()) {

			if (t1.getSecond() < t2.getSecond()) {
				return true;
			}
		
		}
		return false;
	}
	else {
		return false;
	}
}
	