#include "special.h"
#include <iostream>

using namespace std;
SpecialAction::SpecialAction(Board* ptr) : board(ptr) {}

void remove(Board* ptr)
{
	unique_ptr<Board> i (ptr);
}

SpecialAction::~SpecialAction() {
    remove(board);
}

Board * SpecialAction::getBoard() {
    SpecialAction *temp = this;
    while (temp->specialCount != 1) {
        temp = dynamic_cast<SpecialAction *>(temp->board); //casting
    }
    Board *retval = temp->board;
    return retval;
}
