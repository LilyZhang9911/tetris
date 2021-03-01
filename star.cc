#include "star.h"

Star::Star (int level, Board *parent) : Block{level, parent, "*"} {
    int loc = 0;
    while (!parent->getCell(loc, 5)->checkOn()) { //find the bottom location

        if (loc == 17) {
            ++loc;
            break;
        }
        ++loc;
    }
    --loc;
    cells[0] = parent->getCell(loc,5); //store cell as one of its cells
    parent->getCell(loc,5)->turnOn (type); //turn on cell
    cells[0]->setparent(this);
}


bool Star::rotateC() {
    return true;
}


bool Star::rotateCC() {
    return true;
}



