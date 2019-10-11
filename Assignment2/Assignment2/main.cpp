// Created by Isaac Chan on 10/3/19

#include "timespan.h"
#include <cassert>

using namespace std;

void test1() {
	stringstream ss;

    TimeSpan ts(1, 20, 30);
    ss << ts;
	assert(ss.str() == "01:20:30");

    TimeSpan ts2(4, -20, -90);
    ss.str("");
    ss << ts2;
    assert(ss.str() == "03:38:30");

    TimeSpan ts3(1.5, 30.5, -90);
    ss.str("");
    ss << ts3;
	assert(ss.str() == "01:59:00");

    TimeSpan ts4(0, 0.07, 0);
    ss.str("");
    ss << ts4;
	assert(ss.str() == "00:00:04");


	ss.str("");
	TimeSpan ts5(-4, 20, -90);
	ss << ts5;
	assert(ss.str() == "-03:41:30");
}

void test2() {
    TimeSpan ts(1, 20, 30);
    TimeSpan ts2(1, 20, 30);
    TimeSpan ts3(0, 0, 0);

	assert(ts == ts2);
	assert(!(ts != ts2));
	assert(ts != ts3);
    assert((ts + ts + ts) == (ts2 * 3));
    assert((ts * 5) == (ts2 * 4) + ts2);
    assert((ts * 5) == (ts2 * 6) - ts2);
    assert((ts + ts - ts) == ((ts2 * 2) - ts));
    assert((ts - ts2) == ts3);
    assert((ts3 * 5) == ts3);
}

void test3() {
	TimeSpan ts0(0, 1, 61);
	TimeSpan ts1(0, -1, -61);
	TimeSpan ts2 = ts0 - ts1;
	stringstream ss;
	ss << ts2;
	assert(ss.str() == "00:04:02");
}

void testAll() {
    test1();
    test2();
    test3();
}

int main() {
    testAll();
    cout << "Passed all tests. Done." << std::endl;
    return 0;
}