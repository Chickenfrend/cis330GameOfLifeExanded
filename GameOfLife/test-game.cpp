#include <iostream>
#include "game.hpp"
#include "cell.hpp"
#include <ctime>

int main(){
	srand(time(0));
	Game lifeGame;
	int xSize;
	int ySize;
	int stepNum;

	cout << "Please enter the size of the grid (int int): ";
	cin >> xSize >> ySize;
	cout << "Please enter the number of steps (int): ";
	cin >> stepNum;
	
	lifeGame.initGame(xSize, ySize);
	lifeGame.populateGame();
	lifeGame.print();
	lifeGame.run(stepNum);
}
