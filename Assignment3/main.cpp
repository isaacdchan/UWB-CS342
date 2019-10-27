#include <iostream>
#include <sstream>
#include <cassert>

#include "creature.h"
#include "maze.h"


// tests 3 mazes. asserts that the creature's final location is the exit
void test() {
	stringstream ss;

	Maze M1("maze1.txt");
	Maze M2("maze2.txt");
	Maze M3("maze3.txt");

	Creature C1(3, 10);
	Creature C2(1, 4);
	Creature C3(1, 1);

	cout << "Path: " << C1.solve(M1) << endl;
	cout << "Path: " << C2.solve(M2) << endl;
    cout << "Path: " << C3.solve(M3) << endl;
	

	ss << C1;
	assert(ss.str() == "(3, 0)");	
	cout << M1 << endl;

	ss.str("");
	ss << C2;
	assert(ss.str() == "(0, 18)");
	cout << M2 << endl;

	ss.str("");
	ss << C3;
	assert(ss.str() == "(1, 0)");
    cout << M3 << endl;

}

//main function
int main() {
    test();
    cout << "Done!" << std::endl;
    return 0;
}