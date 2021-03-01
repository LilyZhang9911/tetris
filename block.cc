#include "block.h"
#include <iostream>

Block::Block (int level, Board *parent, std::string type): potentialScore {(level + 1) * (level + 1)},
 aliveCells {4}, cells{},  parent{parent}, type{type} {
	if(type == "*")
	{
		aliveCells = 1;
                potentialScore = 25; 
	}
}

Block::~Block() {};

std::string Block::textDisplay(std::string type, int line) {
    std::string text[7][2] = {{"  L        ","LLL        "}, {"J          ", "JJJ        "},
    {"IIII       ", "           "}, {"OO         ", "OO         "}, {" SS        ", "SS         "},
    {"TTT        ", " T         "}, {"ZZ         ", " ZZ        "}};
    if (type == "L") {
        if (line == 0) {
            return text[0][0];
        }
        else {
            return text[0][1];
        }
    }
    else if (type == "J") {
        if (line == 0) {
            return text[1][0];
        }
        else {
            return text[1][1];
        }
    }
    else if (type == "I") {
        if (line == 0) {
            return text[2][0];
        }
        else {
            return text[2][1];
        }
    }
    else if (type == "O") {
        if (line == 0) {
            return text[3][0];
        }
        else {
            return text[3][1];
        }
    }
    else if (type == "S") {
        if (line == 0) {
            return text[4][0];
        }
        else {
            return text[4][1];
        }
    }
    else if (type == "T") {
        if (line == 0) {
            return text[5][0];
        }
        else {
            return text[5][1];
        }
    }
    else if (type == "Z") {
        if (line == 0) {
            return text[6][0];
        }
        else {
            return text[6][1];
        }
    }
    return "";
}

bool Block::shiftL() {
    Cell *tempcells[4]; //temporarily store updated info until move is confirmed to be valid
    turnOffCells(); //turn off all cells to check for overlap later
    int newy;
    //check and update each cell
    for (int i = 0; i < 4; ++i) {
        newy = cells[i]->gety() - 1;
        if (newy < 0) { //check for bound
            turnOnTemp();
            return false;
        }

        Cell *temp = parent->getCell(cells[i]->getx(), newy);
        if (temp->checkOn()) { //check if occupied
            turnOnTemp(); //recover previous location since move is invalid
            return false;
        }
        tempcells[i] = temp; //store in temp
    } // now temp contains all new cells

    for (int i = 0; i < 4; ++i) {
        cells[i] = tempcells[i]; //copy over and update new cells
        cells[i]->setparent(this);
    }
    turnOnCells(type); //turn on the new cells
    return true;
}

bool Block::shiftR() {
    Cell *tempcells[4]; //temporarily store updated info until move is confirmed to be valid
    turnOffCells(); //turn off all cells to check for overlap later
    int newy;
    //check and update each cell
    for (int i = 0; i < 4; ++i) {
        newy = cells[i]->gety() + 1;
        if (newy > 10) { //check for bound
            turnOnTemp();
            return false;
        }

        Cell *temp = parent->getCell(cells[i]->getx(), newy);
        if (temp->checkOn()) { //check if occupied
            turnOnTemp(); //recover previous location since move is invalid
            return false;
        }
        tempcells[i] = temp; //store in temp
    } // now temp contains all new cells
    for (int i = 0; i < 4; ++i) {
        cells[i] = tempcells[i]; //copy over and update new cells
        cells[i]->setparent(this);
    }
    turnOnCells(type); //turn on the new cells
    return true;
}

bool Block::shiftD() {
    Cell *tempcells[4]; //temporarily store updated info until move is confirmed to be valid
    turnOffCells(); //turn off all cells to check for overlap later
    int newx;
    //check and update each cell
    for (int i = 0; i < 4; ++i) {
        newx = cells[i]->getx() + 1;
        if (newx > 17) { //check for bound
                turnOnTemp();
                return false;
        }

        Cell *temp = parent->getCell(newx, cells[i]->gety());
        if (temp->checkOn()) { //check if occupied
                turnOnTemp(); //recover previous location since move is invalid
                return false;
        }
        tempcells[i] = temp; //store in temp
    } // now temp contains all new cells

    for (int i = 0; i < 4; ++i) {
        cells[i] = tempcells[i]; //copy over and update new cells
        cells[i]->setparent(this);
    }
    turnOnCells(type); //turn on the new cells
    return true;
}

void Block::turnOffCells() {
    for (int i = 0; i < 4; ++i) {
        cells[i]->turnOff();
    }
}

void Block::turnOnCells(std::string type) {
    for (int i = 0; i < 4; ++i) {
        cells[i]->turnOn(type);
    }
}

void Block::turnOnTemp() {
    for (int i = 0; i < 4; ++i) {
        cells[i]->turnOnTemp();
    }
}

void Block::drop() {
    while (shiftD()) {}
}

void Block::deleteCell(Cell *deletedCell) {
    if (type != "*") {
        for (int i = 0; i < 4; ++i) {
            if (cells[i] == deletedCell) { // if match, remove from list
                --aliveCells; //reduce number of alive cells
                cells[i] = nullptr; //remove link between cell
            }
        }
    }
    else if (type == "*") {
        --aliveCells;
    } 
}

int Block::aliveCount() {
    return aliveCells;
}

int Block::getScore() {
    return potentialScore;
}

void Block::shiftCell(int xcoord, int ycoord) {
    for (int i = 0; i < 4; ++i) {
        if (cells[i] == nullptr) continue;
        else if ((cells[i]->getx() == xcoord) && (cells[i]->gety() == ycoord)) { //found the corresponding cell
            cells[i] = parent->getCell(xcoord+1,ycoord);
        }
    }
}

bool Block::atBottom () {
    turnOffCells();
    int xcoord;
    for (int i = 0; i < 4; ++i) {
        xcoord = cells[i]->getx();
        if (xcoord == 17 || (parent->getCell(xcoord+1,cells[i]->gety())
            ->checkOn())) {
                turnOnTemp();
                return true;
            }
    }
    turnOnTemp();
    return false;
}

void Block::deactivateScore() {
    potentialScore = 0;
}
