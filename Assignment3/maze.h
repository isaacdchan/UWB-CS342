//
// Created by Yusuf Pisan on 4/18/18.
//

#ifndef ASS3_MAZE_H
#define ASS3_MAZE_H

#include <ostream>
#include <string>

using namespace std;

enum CELL { CLEAR, WALL, PATH, VISITED };

class Maze {
	friend ostream &operator<<(ostream &Out, const Maze &Maze);
private:
	const static int MAX_SIZE = 100;
	char Field[MAX_SIZE][MAX_SIZE];
	int Width, Height;
	int ExitRow, ExitColumn;
public:
	// Maze constructor
	// inputs file that is used to set attributes and shape of Maze
	explicit Maze(const string &FileName);
	// checks if location on Maze is either a wall, dead end, or traveled
	bool isClear(int Row, int Col) const;
	// marks location on Maze as part of route to exit
	void markAsPath(int Row, int Col);
	// marks location on Maze as a visited location but not part of route to exit
	void markAsVisited(int Row, int Col);
	// returns the row the exit location is on
	int getExitRow() const;
	// returns the column the exit location is on
	int getExitColumn() const;
};

#endif //ASS3_MAZE_H
