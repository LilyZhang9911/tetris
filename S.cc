#include "S.h"

//rotation[0] transfers to rotation[1] clockwise
const int rotation[2][4][2] = {{{0, 0}, {1, -1}, {-2, 0}, {-1, -1}},
                                {{0, 0}, {-1, 1}, {2,0}, {1,1}}};

S::S (int level, Board *parent) : Block{level, parent, "S"}, pos {0} {
    //set to top left beginning position
    cells[0] = parent->getCell(3,1); //store cell as one of its cells
    parent->getCell(3,1)->turnOn (type); //turn on cell

    cells[1] = parent->getCell(3,2);
    parent->getCell(3,2)->turnOn (type);

    cells[2] = parent->getCell(4,0);
    parent->getCell(4,0)->turnOn (type);

    cells[3] = parent->getCell(4,1);
    parent->getCell(4,1)->turnOn (type);

    for (int i = 0; i < 4; ++i) { //sets the cell's parent to this block
        cells[i]->setparent(this);
    }
}

bool S::rotateC() {
    int newx, newy;
    Cell *tempcells[4];
    turnOffCells(); // turn off current cells
    for (int i = 0; i < 4; i++) {
       // std::cout<<"before: "<<cells[i]->getx()<<" "<<cells[i]->gety()<<std::endl;
        newx = cells[i]->getx() + rotation[pos][i][0];
        newy = cells[i]->gety() + rotation[pos][i][1];
        //std::cout<<"after: "<<newx<<" "<<newy<<std::endl;
        if ((newx < 0) || (newy < 0) ||(newx > 17) || (newy > 10)) {
            turnOnTemp();
            return false; //check if the rotation is in bound
        }

        if (parent->getCell(newx, newy)->checkOn()) { //check if the cell was previously occupied
            turnOnTemp(); //if true, turn on the old cells and do not rotate
            return false;
        }
        tempcells[i] = parent->getCell(newx,newy); //replace old cell
    }

    for (int i = 0; i < 4; ++i) {
        cells[i] = tempcells[i];
        cells[i]->setparent(this);
    }
    turnOnCells(type);

    //update position for next rotation
    if (pos == 1) {
        pos = 0;
    }
    else {
        pos ++;
    }
  //  std::cout<<"done rotation"<<std::endl;
    return true;
}


bool S::rotateCC() {
    int prevpos = pos; //store position for recovery in case if rotation fails
    Cell *tempcells[4];
    int newx, newy;
    //update position for current rotation
    if (pos == 0) {
        pos = 1;
    }
    else {
        pos--;
    }
    turnOffCells(); // turn off current cells
    for (int i = 0; i < 4; i++) {
        newx = cells[i]->getx() - rotation[pos][i][0];
        newy = cells[i]->gety() - rotation[pos][i][1];
        if ((newx < 0) || (newy < 0) ||(newx > 17) || (newy > 10))  { // check bound
            turnOnTemp(); //recover previous cells
            pos = prevpos;
            return false; //check if the rotation is in bound
        }
        if (parent->getCell(newx, newy)->checkOn()) { //check if the cell was previously occupied
            turnOnTemp(); //if true, turn on the old cells and do not rotate
            pos = prevpos;
            return false;
        }
        tempcells[i] = parent->getCell(newx,newy); //replace old cell
    }

    for (int i = 0; i < 4; ++i) {
        cells[i] = tempcells[i]; //update cells
        cells[i]->setparent(this);
    }
    turnOnCells(type);

    return true;
}
