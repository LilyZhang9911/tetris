#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "board.h"
#include "cell.h"
#include "blockList.h"
using namespace std;

Level::Level(Board* boardPtr, int level) : level(level), board(boardPtr) {}

Level::~Level(){};

Block* Level::checkPenalty() {
	return nullptr;
}

int Level::getLevel(){
	return level;
}

void Level::lineCleared(){}

Block* Level::activate(string type) {
	if (type == "I") {
        return new I{level, board};
	}
	else if (type == "J") {
        return new J{level, board};
   	}
   	else if (type == "L") {
        return new L{level, board};
    }
   	else if (type == "O") {
        return new O{level, board};
	}
 	else if (type == "S") {
        return new S{level, board};
    }
    else if (type == "T") {
        return new T{level, board};
    }
    else if (type == "Z") {
        return new Z{level, board};
    }
	else if (type == "*") {
        return new Star{level, board};
    }
    return nullptr;
}


Level * Level::changeLevel(int newlevel, std::string filename) {
    if ((level == 3) || (level == 4)) { //reduce heavy
        board->subHeavy(1);
    }
    if (newlevel == 0) {
        return new Level0(board, filename);
    }
    else if (newlevel == 1) {
        return new Level1(board);
    }
    else if (newlevel == 2) {
        return new Level2(board);
    }
    else if (newlevel == 3) {
        return new Level3(board);
    }
    else if (newlevel == 4){
        return new Level4(board);
    }
    return nullptr;
}
