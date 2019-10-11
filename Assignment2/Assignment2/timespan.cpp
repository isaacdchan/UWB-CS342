// Created by Isaac Chan on 10/3/19

#include "timespan.h"

TimeSpan::TimeSpan(double Hour, double Minute, double Second) {
	this->Hour = Hour;
	this->Minute = Minute;
	this->Second = Second;
	
	this->totalSeconds = 0;
	CalculateSeconds();
	AggregateSeconds();
}

TimeSpan::~TimeSpan() {
	//cout << "Horatio, I am dead." << endl;
}

void TimeSpan::CalculateSeconds() {
	totalSeconds += Second;
	totalSeconds += Hour * 3600;
	totalSeconds += Minute * 60;
}

void TimeSpan::AggregateSeconds() {
	Minute = (int)totalSeconds / 60;
	Second = std::fmod(totalSeconds, 60.0);

	Hour = (int)Minute / 60;
	Minute = std::fmod(Minute, 60.0);

	Minute = abs(Minute);
	Second = floor(abs(Second));
}

TimeSpan TimeSpan::operator+(const TimeSpan &Ts) {
  double Sum = totalSeconds + Ts.totalSeconds;

  TimeSpan TsSum(0, 0, Sum);

  return TsSum;
}

TimeSpan TimeSpan::operator-(const TimeSpan &Ts) {
	double Difference = totalSeconds - Ts.totalSeconds;

	TimeSpan TsSum(0, 0, Difference);

	return TsSum;
}

TimeSpan TimeSpan::operator*(int Multiplier) {
	double Product = totalSeconds * Multiplier;

	TimeSpan TsSum(0, 0, Product);

	return TsSum;
}

bool TimeSpan::operator==(const TimeSpan &Ts) {
	return totalSeconds == Ts.totalSeconds;
}

bool TimeSpan::operator!=(const TimeSpan &Ts) {
	return totalSeconds != Ts.totalSeconds;
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

	if (Ts.totalSeconds < 0 && stringHour[0] != '-') {
		stringHour = "-" + stringHour;
	}

	Out << stringHour << ":" << stringMinute << ":" << stringSecond;
	return Out;
}
