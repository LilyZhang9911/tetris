#include "O.h"

O::O (int level, Board *parent) : Block{level, parent, "O"}, pos {0} {
    //set to top left beginning position
    cells[0] = parent->getCell(3,0); //store cell as one of its cells
    parent->getCell(3,0)->turnOn (type); //turn on cell

    cells[1] = parent->getCell(3,1);
    parent->getCell(3,1)->turnOn (type);

    cells[2] = parent->getCell(4,0);
    parent->getCell(4,0)->turnOn (type);

    cells[3] = parent->getCell(4,1);
    parent->getCell(4,1)->turnOn (type);

    for (int i = 0; i < 4; ++i) { //sets the cell's parent to this block
        cells[i]->setparent(this);
    }
}

bool O::rotateC() {
    return true;
}


bool O::rotateCC() {
    return true;
}


