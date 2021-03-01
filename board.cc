#include "board.h"
#include <iostream>
#include "block.h"
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"


Board::Board (): board {}, score{0}, file(""), specialAvailable(false), heavy{0}, gameEnd {false},
curLevel {nullptr}, endRound {false}, curBlock {nullptr}, nextBlock {""}, blocks{}, specialCount {0} {
    for (int i = 0; i < 18; ++i) {
            board.emplace_back(std::vector<Cell>());
        for (int j = 0; j < 11; ++j) {
            Cell newcell{i, j};
            board[i].emplace_back (newcell);
        }
    }
    std::vector <Block *> blocks;
}

Board::~Board () {
    for (int i = 0; i < 18; ++i) {
        board[i].clear();
    }
    board.clear();
    blocks.clear();
}


void Board::setFile(std::string file) {
	this->file = file;
}

int Board::getLevel() {
	return curLevel->getLevel();
}

void Board::levelUp(int n) {
	int lv = curLevel->getLevel();
	int newlv = (lv+n)>4? 4: (lv+n);
	if (lv < 4) {
		curLevel.reset(curLevel->changeLevel(newlv, file));
	}
}

void Board::levelDown(int n) {
	int lv = curLevel->getLevel();
	int newlv = (lv-n)<0? 0: (lv-n);
	if (lv > 0) {
		curLevel.reset(curLevel->changeLevel(newlv, file));
	}
}

std::string Board::printrow(int row) {
    std::string retval = "";
    for (int j = 0; j < 11; ++j) {
        retval += board[row][j].print();
    }
    return retval;
}

Cell *Board::getCell(int x, int y) {
    return &(board[x][y]);
}


void Board::resetBlock(std::string type) {
    //delete old
    blocks.pop_back();

    curBlock->turnOffCells(); //turn off all cur cells
	curBlock.reset (curLevel->activate(type));
	blocks.push_back(curBlock); //add new
}

bool Board::checkEnd(std::string type) {
    if (type == "*") {
        if (board[5][0].checkOn()) {
            return true;
        }
    }
    else if (type == "I") {
        if (board[3][0].checkOn() || board[3][1].checkOn() ||
            board[3][2].checkOn() || board[3][3].checkOn()) {
                    return true;
            }
    }
    else if (type == "J") {
        if (board[3][0].checkOn() || board[4][0].checkOn() ||
             board[4][1].checkOn() || board[4][2].checkOn()) {
                 return true;
             }
    }
    else if (type == "L") {
        if (board[3][2].checkOn() || board[3][1].checkOn() ||
            board[3][2].checkOn() || board[3][3].checkOn()) {
                return true;
        }
    }
    else if (type == "O") {
            if (board[3][0].checkOn() || board[3][1].checkOn() ||
                 board[4][0].checkOn() || board[4][1].checkOn()) {
                return true;
        }
    }
    else if (type == "S") {
        if (board[3][1].checkOn() || board[3][2].checkOn() ||
            board[4][0].checkOn() || board[4][1].checkOn()) {
                return true;
        }
    }
    else if (type == "T") {
        if (board[3][0].checkOn() || board[3][1].checkOn() ||
            board[3][2].checkOn() || board[4][1].checkOn()) {
                return true;
        }
    }
    else { //Z case
         if (board[3][0].checkOn() || board[3][1].checkOn() ||
              board[4][1].checkOn() || board[4][2].checkOn()) {
                return true;
        }
    }
    return false;
}


void Board::changeLevel(int newlevel) {
   if (curLevel == nullptr) {
        curLevel.reset(new Level1(this));
        nextBlock = curLevel->makeBlock(); //make next block
    }
   curLevel.reset(curLevel->changeLevel(newlevel, file)); 
   if (newlevel == 0) {
       nextBlock =  curLevel->makeBlock(); 
   }
}


void Board::nextRound(std::string newBlock) {
    if (newBlock != "") {
        nextBlock = newBlock;
    }
    if (checkEnd(nextBlock)) {
        gameEnd = true; //check if the new block fits
    }
    else {
        curBlock.reset(curLevel->activate(nextBlock));
        blocks.emplace_back(curBlock);
        nextBlock = curLevel->makeBlock();
    }
}

void Board::scoreBlock() {
    for (unsigned int i = 0; i < blocks.size(); ++i) {
        if (blocks[i]->aliveCount() == 0) {
            score += blocks[i]->getScore();
            blocks[i]->deactivateScore();
        }
    }
}


void Board::clearLine() {
    int linesCleared = 0;
    int counter = 0;
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 11; ++j) {
            if (board[i][j].checkOn()) {
                ++counter;
            }
        }
        if (counter == 11) {
	    linesCleared++;
            for (int k = 0; k < 11; ++k) {
                board[i][k].reportDelete();
            }
            shiftBoard(i);
        }
        counter = 0;
    }
    if (linesCleared > 0) {
        curLevel->lineCleared();
        if (linesCleared >= 2) {
            specialAvailable = true;
        }
        score += ((linesCleared + curLevel->getLevel()) * (linesCleared + curLevel->getLevel()));
    }
    else {
        Block* penalty = curLevel->checkPenalty();
    	if (penalty != nullptr) {
    	    if (checkEnd("*")) {
                gameEnd = true;
    	    }
		blocks.emplace_back(penalty);
		clearLine(); //!clear again after adding a penalty block
        }
    }
}

void Board::shiftBoard(int row) {
    for (int i = row; i > 0; --i) {
        board[i] = board[i-1]; //copy value of next cell
        for (int j = 0; j < 11; ++j) {
            board[i][j].shiftDown(); //shift the cells down
        }
    } //all cells shifted
    for (int k = 0; k < 11; ++k) {
        board[0][k].reset(0, k); //reset top row
    }
}


int Board::getScore() {
    return score;
}

void Board::makeNextBlock() {
    nextBlock = curLevel->makeBlock();
}

void Board::blockRotateC(int n) {
    int i = n;
    while (i > 0) {
        curBlock->rotateC();
        --i;
    }

    if (heavy > 0) {
        curBlock->shiftD();
        if (curBlock->atBottom()) {
            endRound = true;
        }
    }
}
void Board::blockRotateCC(int n) {
    int i = n;
    while (i > 0) {
        curBlock->rotateCC();
        --i;
    }

    if (heavy > 0) {
        curBlock->shiftD();
        if (curBlock->atBottom()) {
            endRound = true;
        }
    }
}

void Board::blockShiftR(int n) {
    int i = n;
    while (i > 0) {
        curBlock->shiftR();
        --i;
    }

    for (int i = 0; i < heavy; ++i) {
        curBlock->shiftD();
        if (curBlock->atBottom()) {
            endRound = true;
        }
    }
}

void Board::blockShiftL(int n) {
    for (int i = 0; i < heavy; ++i) {
        curBlock->shiftD();
        if (curBlock->atBottom()) {
            endRound = true;
        }
    }
    int i = n;
    while (i > 0) {
        curBlock->shiftL();
        --i;
    }
}
bool Board::blockShiftD(int n) {
    int i = n;
    while (i > 0 && curBlock->shiftD()) {
        --i;
    }
    //evaluate at the end
    if (i == 0) return true;
    return false;
}
void Board::blockDrop() {
    curBlock->drop();
}

Board *Board::getBoard() {
    return this;
}

bool Board::getSpecial() {
    return specialAvailable;
}

void Board::turnoffSpecial() {
    specialAvailable = false;
}

void Board::endAction() {
}

void Board::addHeavy(int n) {
    heavy += n;
}

bool Board::getGameEnd() {
    return gameEnd;
}

bool Board::getEndRound() {
    return endRound;
}

void Board::turnOffEndRound() {
    endRound = false;
}

void Board::subHeavy(int n) {
    heavy -= n;
}

std::string Board::printNext(int n) {
    return curBlock->textDisplay(nextBlock, n);
}

std::string Board::printNext()
{
	return nextBlock;
}
