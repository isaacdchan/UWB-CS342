#include <iostream>

#include "creature.h"
#include "maze.h"


void test() {
    Maze M("maze2.txt");
    // cout << m << endl;
    Creature C(3, 1);
    cout << "Path: " << C.solve(M) << endl;
    cout << M << endl;
}
int main() {
    test();
    cout << "Done!" << std::endl;
    return 0;
}