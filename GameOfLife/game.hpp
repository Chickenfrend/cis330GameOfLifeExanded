#ifndef __GAME
#define __GAME

#include <iostream>
#include <vector>
#include "cell.hpp"
using namespace std;

class Game{
	public:
		void step();
		void run(int steps);
		void print();
		void initGame(int xSize, int ySize);
		void populateGame();
	private:
		int hSize;
		int vSize;
		void updateCell(int i, int j);
		void moveFarmer(int i, int j);
		vector<vector<Cell>> gameVec;	
		vector<vector<Cell>> tempVec;
};

#endif
