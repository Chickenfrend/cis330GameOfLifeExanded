#include <iostream>
#include <vector>
#include "game.hpp"

void Game::step(){
	int i = 0;
	int j = 0;

	//I opted to go for the two vector approach
	//Updating in real time caused some weird behavior.
	tempVec = gameVec;
	//I attempted to use iterators, but still had to pass normal indices...
	vector<vector<Cell>>::iterator it = gameVec.begin();
	for(it = gameVec.begin(); it != gameVec.end(); it++){
		for(vector<Cell>::iterator ij = (*it).begin(); ij != (*it).end(); ij++){
			updateCell(i,j);
			j++;
		}
		j = 0;
		i++;
	}
	gameVec = tempVec;
}

//This iterates the game steps times, but it also
//contains some printed stuff. I wanted to keep the print
//function general use.
void Game::run(int steps){
    for(int i = 0; i < steps; i++){
        step();
		cout << endl << endl;
		cout << "Iteration " << i + 1 << endl;
        print();
    }
}

//Most of the work happens here. Updates one time.
void Game::updateCell(int i, int j){
	//wolf, sheep, farmer, and empty count.
	int wCount = 0;
	int sCount = 0;
	int fCount = 0;
	int eCount = 0;
	//Making ths variable allows us to modify the cell,
	//and prevents the other if statements that change cells
	//from being activated.
	char currentCellChar = gameVec[i][j].getCellType();

	//So, this iterates through the squares around the current position. The modular arithmetic lets
	//the board loop around. The weird way it accesses elements is to prevent overflow by access to negative indices.
	for(int n = i-1; n < i+2; n++){
		for(int m = j-1; m < j+2; m++){
			if(gameVec[(n % hSize + hSize) % hSize][(m % vSize % vSize) % vSize].getCellType() == 'W'){
				wCount++;
			}
			if(gameVec[(n % hSize + hSize) % hSize][(m % vSize % vSize) % vSize].getCellType() == 'S'){
				sCount++;
			}
			if(gameVec[(n % hSize + hSize) % hSize][(m % vSize % vSize) % vSize].getCellType() == 'F'){
				fCount++;
			}
			if(gameVec[(n % hSize + hSize) % hSize][(m % vSize % vSize) % vSize].getCellType() == '.'){
				eCount++;
			}
		}
	}

	//This just checks conditions and does what the rules say to do to each position.	
	if(currentCellChar == '.'){
		if(sCount == 2){
			tempVec[i][j].setCellType('S');
		}
		else if(wCount == 2){
			tempVec[i][j].setCellType('W');
		}
		else if(fCount == 2){
			tempVec[i][j].setCellType('F');
		}
	}
	else if(currentCellChar == 'S'){
		if((sCount > 3) || (wCount >= 1)){
			tempVec[i][j].setCellType('.');
		}
	}
	else if(currentCellChar == 'W'){
		if((fCount > 0) || (wCount > 3) || ((wCount + eCount) == 8)){
			tempVec[i][j].setCellType('.');
		}
	}
	else if(currentCellChar == 'F'){
		if(eCount > 0){
			moveFarmer(i, j);
		}
	}
	else{
		cout << "Error: Out of bounds (wrong character)." << endl;
	}

	gameVec = tempVec;
}

//Here pointers to elements are loaded into a vector, and random selection occurs.
//Allows us to move farmer.
void Game::moveFarmer(int i, int j){
	vector<Cell*> cellPointer;
	int eCount = 0;

	for(int n = i-1; n < i+2; n++){
		for(int m = j-1; m < j+2; m++){
			if(gameVec[(n % hSize + hSize) % hSize][(m % vSize + vSize) % vSize].getCellType() == '.'){
				cellPointer.push_back(&(tempVec[(n % hSize + hSize) % hSize][(m % vSize + vSize) % vSize]));
				eCount++;
			}
		}
	}
	
	(*cellPointer[(rand() % eCount + eCount) % eCount]).setCellType('F');

	tempVec[i][j].setCellType('.');

}

//I'm not sure if each vector needs to be seperately initialized, but I was
//having some weird issues and initializing each vector was an attempt to fix it.
void Game::initGame(int xSize, int ySize){
	hSize = xSize;
	vSize = ySize;
	gameVec.resize(xSize);	
	tempVec.resize(xSize);

	vector<vector<Cell>>::iterator it = gameVec.begin();
	for(it = gameVec.begin(); it != gameVec.end(); it++){
		(*it).resize(ySize);
	}

	for(it = tempVec.begin(); it != tempVec.end(); it++){
		(*it).resize(ySize);
	}
}

//This randomly generates a starting field. The numbers here are rather arbitrary, 
//I just selected them through trial and error. Farmers tend to dominate long term due to their immortality,
//but if you have too many wolves you won't get too many sheep. A nice balance is most interesting.
void Game::populateGame(){
	int randInt;
	vector<vector<Cell>>::iterator it = gameVec.begin();
	for(it = gameVec.begin(); it != gameVec.end(); it++){
		for(vector<Cell>::iterator ij = (*it).begin(); ij != (*it).end(); ij++){
			randInt = rand() % 100;
			if(randInt < 65){
				(*ij).setCellType('.');
			}
			else if(randInt <= 82){
				(*ij).setCellType('S');
			}
			else if(randInt <= 87){
				(*ij).setCellType('F');
			}
			else{
				(*ij).setCellType('W');
			}
		}
	}
	
	//Again, not sure if this is necessary. Did it while fixing a weird issue I had when I decided to impliment
	//a new vector to act as an intermediate vector.
	for(it = tempVec.begin(); it != tempVec.end(); it++){
		for(vector<Cell>::iterator ij = (*it).begin(); ij != (*it).end(); ij++){
			(*ij).setCellType('.');	
		}
	}
}

void Game::print(){
	vector<vector<Cell>>::iterator it = gameVec.begin();
	for(it = gameVec.begin(); it != gameVec.end(); it++){
		for(vector<Cell>::iterator ij = (*it).begin(); ij != (*it).end(); ij++){
			cout << (*ij).getCellType() << " ";
		}
		cout << endl;
	}
}

