#include "blind.h"
#include <iostream>


Blind::Blind(Board* ptr): SpecialAction(ptr) {
    ++specialCount;
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 11; ++j) {
            if( i>= 6 && i <= 15 && j >= 2 && j <=8)  {
                board->getCell(i,j)->hide();
            }
        }
    }
}

void Blind::endAction() {
    for (int i = 0; i < 18; ++i) {
        for (int j = 0; j < 11; ++j) {
            if( i>= 6 && i <= 15 && j >= 2 && j <=8)  {
                board->getCell(i,j)->unhide();
            }
        }
    }
}

