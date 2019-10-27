#include "creature.h"

// operator overload for <<. returns "(Creature.Row, Creature.Col)"
ostream& operator<<(ostream& Out, const Creature& Creature) {
	Out << "(" << Creature.Row << ", " << Creature.Col << ")";
	return Out;
}

// Creature constructor. takes in the starting postion's Row and Column
Creature::Creature(int Row, int Col) : Row(Row), Col(Col) {}

// returns whether the Creature is at the exit position
bool Creature::atExit(const Maze &Maze) const {
	return Row == Maze.getExitRow() && Col == Maze.getExitColumn();
}
// inputs the Maze object to solve. returns the final path from start to exit
string Creature::solve(Maze &Maze) {
	string Path = explore(Maze);

	return Path;
}
// checks if path is clear in each direction. if so, moves Creature said direction 
// if results in a dead end, mark as visited. else, mark as path
string Creature::explore(Maze& Maze) {
	string Path = "X";


	Maze.markAsPath(Row, Col);

	if (atExit(Maze))
		return "";

	if (Maze.isClear(Row - 1, Col)) {
		Path = goNorth(Maze);
	}
	if (Maze.isClear(Row, Col + 1)) {
		Path = goEast(Maze);
	}
	if (Maze.isClear(Row + 1, Col)) {
		Path = goSouth(Maze);
	}
	if (Maze.isClear(Row, Col - 1)) {
		Path = goWest(Maze);
	}

	if (Path == "X") {
		Maze.markAsVisited(Row, Col);
		return "X";
	}

	return Path;
}
// moves Creature to next location
// if next location results in dead end, moves creature back to previous location and returns "X"
// else adds direction to Path and continues exploring
string Creature::goDirection(Maze& Maze, int Row, int Col, string Direction) {
	this->Row += Row;
	this->Col += Col;

	string Path = explore(Maze);
	if (Path == "X") {
		this->Row -= Row;
		this->Col -= Col;
		return "X";
	}

	return Direction + Path;
}
// moves Creature north
string Creature::goNorth(Maze &Maze) {
	return goDirection(Maze, -1, 0, "N");
}
// moves Creature east
string Creature::goEast(Maze& Maze) {
	return goDirection(Maze, 0, 1, "E");
}
// moves Creature south
string Creature::goSouth(Maze& Maze) {
	return goDirection(Maze, 1, 0, "S");
}
// moves Creature west
string Creature::goWest(Maze& Maze) {
	return goDirection(Maze, 0, -1, "W");
}

