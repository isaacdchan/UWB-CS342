// Created by Isaac Chan on 10/3/19

#include <cmath>
#include "timespan.h"


// overflow, negatives, decimals
TimeSpan::TimeSpan(double Hour, double Minute, double Second) {
	Hour = Hour;
	Minute = Minute;
	Second = Second;

	double hourDecimal = std::fmod(Hour, 1);
	if (hourDecimal != 0) {
		Minute += (hourDecimal * 60);
	}
	   
	double minuteDecimal = std::fmod(Minute, 1);
	if (minuteDecimal != 0) {
		Second += (minuteDecimal * 60);
		Second = floor(Second);
	}

	double minFromSec = Second / 60;
	double remainingSec = std::fmod(Second, 60.0);

	Minute += minFromSec;
	double hourFromMin = Minute / 60;
	double remaningMin = std::fmod(Minute, 60.0);

	Hour += hourFromMin;
	Minute = remaningMin;
	Second = remainingSec;
}

TimeSpan::~TimeSpan() {
	cout << "Horatio, I am dead." << endl;
}

void TimeSpan::Normalize() {

}

TimeSpan TimeSpan::operator+(const TimeSpan &Ts) {
  TimeSpan TsSum;
  double hours = Hour + Ts.Hour;
  return TsSum;
}

TimeSpan TimeSpan::operator-(const TimeSpan &Ts) {
  TimeSpan TsSub;
  return TsSub;
}

TimeSpan TimeSpan::operator*(int Number) {
  TimeSpan TsLarge;
  return TsLarge;
}

bool TimeSpan::operator==(const TimeSpan &Ts) {
  return true;
}

bool TimeSpan::operator!=(const TimeSpan &Ts) {
  return true;
}

ostream& operator<<(ostream& Out, const TimeSpan& Ts) {
	Out << Ts.Hour << ':' << Ts.Minute << ':' << Ts.Second << endl;
	return Out;
}
