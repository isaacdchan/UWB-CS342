#include "creature.h"



std::ostream &operator<<(std::ostream &Out, const Creature &Creature) {
	return Out;
}

Creature::Creature(int Row, int Col) : Row(Row), Col(Col) {}

bool Creature::atExit(const Maze &Maze) const {
	if (Row == Maze.getExitRow() && Col == Maze.getExitColumn()) {
		return true;
	}
}

string Creature::solve(Maze &Maze) {
	string Path = explore(Maze);

	return Path;
}

string Creature::explore(Maze& Maze) {
	cout << "EXPLORING: " << Row << "," << Col << endl;
	string Path = "X";

	Maze.markAsPath(Row, Col);

	if (Row == Maze.getExitRow() && Col == Maze.getExitColumn())
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

string Creature::goNorth(Maze &Maze) {
	return goDirection(Maze, -1, 0, "N");
}
string Creature::goEast(Maze& Maze) {
	return goDirection(Maze, 0, 1, "E");
}
string Creature::goSouth(Maze& Maze) {
	return goDirection(Maze, 1, 0, "S");
}
string Creature::goWest(Maze& Maze) {
	return goDirection(Maze, 0, -1, "W");
}