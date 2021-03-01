#include "level4.h"
#include "board.h"
#include <cstdlib>
#include <math.h>

std::string Level4::makeBlock() {
	int rnd = floor(rand() % 9 + 1);
	switch (rnd)
	{
		case 1: return "O";
		case 2: return "I";
		case 3: return "J";
		case 4: return "L";
		case 5: return "T";
		case 6: case 7: return "S";
		case 8: case 9: return "Z";
	}

	return nullptr;
}

Level4::Level4(Board *boardPtr) : Level(boardPtr, 4), noClearCount(0) {
    board->addHeavy(1);
}

void Level4::lineCleared() {
	noClearCount = 0;
}

Block* Level4::checkPenalty() {
	noClearCount++;
	if (noClearCount == 5) {
		Block* penalty = activate("*");
		noClearCount = 0; //reset count after adding
		return penalty;
	}
	return nullptr;
}
