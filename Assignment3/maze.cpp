#include <fstream>
#include <iostream>
#include "maze.h"

using namespace std;
// operator overload for Maze object. returns visual representation of Maze
ostream &operator<<(ostream &Out, const Maze &Maze) {
	for (int Row = 0; Row < Maze.Height; ++Row) {
		for (int Col = 0; Col < Maze.Width; ++Col) {
			Out << Maze.Field[Row][Col]; // NOLINT
		}
		Out << endl;
		}
		Out << endl;
	return Out;
}

// For Clion, need the following line in CMakeLists.txt so maze.txt is found
// at the same location as the cpp files
// # need to load data files from current directory as cpp files
// set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

// Maze constructor
// inputs file that is used to set attributes and shape of Maze
Maze::Maze(const string &FileName) {
	ifstream InFile;
	InFile.open(FileName);
	if (!InFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}
	InFile >> Width >> Height;
	InFile >> ExitRow >> ExitColumn;
	string Str;
	getline(InFile, Str);
	for (int Row = 0; Row < Height; ++Row) {
		for (int Col = 0; Col < Width; ++Col) {
			InFile.get(Field[Row][Col]); // NOLINT
		}
		getline(InFile, Str);
	}

}

// returns the row the exit location is on
int Maze::getExitRow() const {
	return ExitRow;
}

// returns the column the exit location is on
int Maze::getExitColumn() const {
	return ExitColumn;
}

// checks if location on Maze is either a wall, dead end, or traveled
bool Maze::isClear(int Row, int Col) const {
	return Field[Row][Col] == ' '; // NOLINT
}

// marks location on Maze as part of route to exit
void Maze::markAsPath(int Row, int Col) {
	Field[Row][Col] = '*'; // NOLINT
}

// marks location on Maze as a visited location but not part of route to exit
void Maze::markAsVisited(int Row, int Col) {
	Field[Row][Col] = '+'; // NOLINT
}
