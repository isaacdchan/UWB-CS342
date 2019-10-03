//
// TODO Created by XXX on YYY.
//

#ifndef ASS2_TIMESPAN_H
#define ASS2_TIMESPAN_H

#include <iostream>

using namespace std;

class TimeSpan {
  friend ostream &operator<<(ostream &Out, const TimeSpan &Ts);
public:
  // explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
  explicit TimeSpan(double Hour = 0, double Minute = 0, double Second = 0);
  // add
  TimeSpan operator+(const TimeSpan &Ts);
  // subtract
  TimeSpan operator-(const TimeSpan &Ts);
  // check equality
  bool operator==(const TimeSpan &Ts);
  // check if not equal
  bool operator!=(const TimeSpan &Ts);
  // multiply timespan by a number
  TimeSpan operator*(int Number);
private:

};

#endif //ASS2_TIMESPAN_H
