//
// Created by Yusuf Pisan on 4/18/18.
//

#ifndef ASS3_CREATURE_H
#define ASS3_CREATURE_H

#include "maze.h"
#include <iostream>
#include <ostream>

using namespace std;

class Creature {
public:
	// operator overload for <<. returns "(Creature.Row, Creature.Col)"
	friend ostream &operator<<(ostream &Out, const Creature &Creature);

private:
	int Row;
	int Col;

public:
	// Creature constructor. takes in the starting postion's Row and Column
	Creature(int Row, int Col);

	// inputs the Maze object to solve. returns the final path from start to exit
	string solve(Maze &Maze);
	// returns whether the Creature is at the exit position
	bool atExit(const Maze &Maze) const;
	// checks if path is clear in each direction. if so, moves Creature said direction 
	// if results in a dead end, mark as visited. else, mark as path
	string explore(Maze& Maze);
	// moves Creature to next location
	// if next location results in dead end, moves creature back to previous location and returns "X"
	// else adds direction to Path and continues exploring
	string goDirection(Maze& Maze, int Row, int Col, string Direction);
	// moves Creature north
	string goNorth(Maze &Maze);
	// moves Creature east
	string goEast(Maze &Maze);
	// moves Creature south
	string goSouth(Maze& Maze);
	// moves Creature west
	string goWest(Maze &Maze);
};

#endif //ASS3_CREATURE_H
