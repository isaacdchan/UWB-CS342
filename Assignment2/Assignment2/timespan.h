// Created by Isaac Chan on 10/3/19

#ifndef ASS2_TIMESPAN_H
#define ASS2_TIMESPAN_H

#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

class TimeSpan {
  friend ostream &operator<<(ostream &Out, const TimeSpan &Ts);
public:
  explicit TimeSpan(double Hour = 0, double Minute = 0, double Second = 0);
  virtual ~TimeSpan();

  //convert decimal values in larger units to whole numbers in smaller units
  void CalculateSeconds();
  //combine smaller units into larger units
  void AggregateSeconds();

  // add
  TimeSpan operator+(const TimeSpan &Ts);
  // subtract
  TimeSpan operator-(const TimeSpan &Ts);
  // check equality
  bool operator==(const TimeSpan &Ts);
  // check if not equal
  bool operator!=(const TimeSpan &Ts);
  // multiply timespan by a number
  TimeSpan operator*(int Multiplier);

private:
	double Hour;
	double Minute;
	double Second;
	double totalSeconds;
};

#endif //ASS2_TIMESPAN_H
