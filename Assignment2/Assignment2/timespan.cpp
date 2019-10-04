// Created by Isaac Chan on 10/3/19

#include "timespan.h"


TimeSpan::TimeSpan(double Hour, double Minute, double Second) {
	this->Hour = Hour;
	this->Minute = Minute;
	this->Second = Second;

	Normalize();
}

TimeSpan::~TimeSpan() {
	//cout << "Horatio, I am dead." << endl;
}

void TimeSpan::Normalize() {
	RemoveDecimals();
	AggregateUnits();
	ApplyNegatives();
}

void TimeSpan::RemoveDecimals() {
	double hourDecimal = std::fmod(Hour, 1);
	if (hourDecimal != 0) {
		Hour = floor(Hour);
		Minute += (hourDecimal * 60);
	}
	double minuteDecimal = std::fmod(Minute, 1);
	if (minuteDecimal != 0) {
		Minute = floor(Minute);
		Second += (minuteDecimal * 60);
		Second = floor(Second);
	}
}

void TimeSpan::AggregateUnits() {
	double minFromSec = (int)Second / 60;
	double remainingSec = std::fmod(Second, 60.0);

	Minute += minFromSec;
	double hourFromMin = (int)Minute / 60;
	double remaningMin = std::fmod(Minute, 60.0);

	Hour += hourFromMin;
	Minute = remaningMin;
	Second = remainingSec;
}

void TimeSpan::ApplyNegatives() {
	if (Second < 0) {
		Minute -= 1;
		Second = 60 + Second;
	}
	if (Minute < 0) {
		Hour -= 1;
		Minute = 60 + Minute;
	}

	Second == -0 ? Second = 0 : Second;
	Minute == -0 ? Minute = 0 : Minute;
	Hour == -0 ? Hour = 0 : Hour;
}

string TimeSpan::stringify(double value) {
	stringstream ss;
	ss << value;
	std::string stringValue = ss.str();

	value < 10 ? stringValue = "0" + stringValue : stringValue;

	return stringValue;
}

TimeSpan TimeSpan::operator+(const TimeSpan &Ts) {
  double _Hour = Hour + Ts.Hour;
  double _Minute = Minute + Ts.Minute;
  double _Second = Second + Ts.Second;
  
  TimeSpan TsSum(Hour = _Hour, Minute = _Minute, Second = _Second);

  return TsSum;
}

TimeSpan TimeSpan::operator-(const TimeSpan &Ts) {
	double _Hour = Hour - Ts.Hour;
	double _Minute = Minute - Ts.Minute;
	double _Second = Second - Ts.Second;

	TimeSpan TsSub(Hour = _Hour, Minute = _Minute, Second = _Second);

	return TsSub;
}

TimeSpan TimeSpan::operator*(int Multiplier) {
	double _Hour = Hour * Multiplier;
	double _Minute = Minute * Multiplier;
	double _Second = Second * Multiplier;

	TimeSpan TsLarge(Hour = _Hour, Minute = _Minute, Second = _Second);

	return TsLarge;
}

bool TimeSpan::operator==(const TimeSpan &Ts) {
	return Hour == Ts.Hour && Minute == Ts.Minute && Second == Ts.Second;
}

bool TimeSpan::operator!=(const TimeSpan &Ts) {
	return Hour != Ts.Hour or Minute != Ts.Minute or Second != Ts.Second;
}


ostream& operator<<(ostream& Out, const TimeSpan& Ts) {
	auto stringify = [](double value) {
		stringstream ss;
		ss << value;
		std::string stringValue = ss.str();

		value > -10 && value < 0 ? stringValue = stringValue.insert(1, "0") : stringValue;
		value >= 0 && value < 10 ? stringValue = "0" + stringValue : stringValue;

		return stringValue;
	};

	string stringHour = stringify(Ts.Hour);
	string stringMinute = stringify(Ts.Minute);
	string stringSecond = stringify(Ts.Second);


	Out << stringHour << ":" << stringMinute << ":" << stringSecond;
	return Out;
}
