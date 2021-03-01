#ifndef cell_h
#define cell_h
#include <iostream>

class Block; //forward declaration

class Cell {
    bool occupied;
    bool hidden;
    std::string type;
    //coordinates
    int x;
    int y;
    Block *parent;

public:
    // cell does not have any heap memory, so default destructor is enough
    Cell(int xcoord, int ycoord); //constructor
    int getx(); //row
    int gety(); //column
    bool checkOn(); //returns true if the cell is occupied
    void turnOn(std::string t); //turn on the cell using a block type
    void turnOff(); //turn off the cell
    void hide(); //turns on hidden for blind
    void unhide(); //turn off hidden for blind
    void setparent(Block *parent); //set cell parent to a block
    std::string print(); //print the cell type by returning the type of block or '-' if not occupied
    void turnOnTemp(); //turns on all cells that were temporarily turned off, called by block only
    void reportDelete(); //board calls this to check if the cell is deleted
    void shiftDown(); //shifts the x coordinate one unit down, used when line is cleared
    void reset(int x, int y); //resets the cell to initial state
};
#endif

