#include "cell.h"
#include <iostream>

#include "block.h"

Cell::Cell(int xcoord, int ycoord): occupied{false}, hidden(false), type{""}, x{xcoord}, y{ycoord}, parent {nullptr} {}

int Cell::getx() {
    return x;
}

int Cell::gety() {
    return y;
}

void Cell::hide () {
    hidden = true;
}

void Cell::unhide() {
    hidden = false;
}

void Cell::turnOn(std::string t)  {
    type = t;
    occupied = true;
}

void Cell::turnOff()  {
    occupied = false;
}

bool Cell::checkOn() {
    return occupied;
}


std::string Cell::print() {
    std::string retval = "";
    if (hidden)
    {
	retval += "?";
    } else if(!occupied){
	retval += "-";
    }
    else {
        retval += type;
    }
    return retval;
}

void Cell::setparent(Block *setval) {
    parent = setval;
}


void Cell::reportDelete() {
    if (occupied) { //if it has a parent
        parent->deleteCell(this); //tell parent it is deleted, since the row will be deleted
    }
    occupied = false; //turn off itself
}

void Cell::turnOnTemp() {
    occupied = true;
}

void Cell::shiftDown() {
    if (occupied) {
        parent->shiftCell(x, y);
    }
    x = x + 1;
}

void Cell::reset (int x, int y) {
    this->x = x;
    this->y = y;
    occupied = false;
    type = "";
    parent = nullptr;
}
