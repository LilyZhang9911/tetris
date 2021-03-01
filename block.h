#ifndef block_h
#define block_h
#include <vector>
#include "board.h"
#include "cell.h"

class Block {
    int potentialScore, aliveCells;
protected:
    Cell *cells[4];
    Board *parent;
    std::string type;
    void turnOnCells(std::string); //turn on all cells with a given type
    void turnOnTemp(); //turn on all temporarily turned off cells
public:
    Block (int potentialScore, Board *parent, std::string type);
    virtual ~Block();
    void turnOffCells(); //turn off all cells
    virtual bool rotateC() = 0; //return false when it cannot be rotated
    virtual bool rotateCC() = 0;
    //moving blocks
    bool shiftL();
    bool shiftR();
    bool shiftD();
    void drop();

    std::string textDisplay (std::string type, int line);

    int aliveCount(); //return number of cells still on
    int getScore(); //returns score of the block
    void shiftCell(int x, int y); //shift the pointer of a cell down, used when a row is deleted
    void deleteCell(Cell *deletedCell); //delete the cell that matches the given pointer
    void checkBlock(); //check if entire block cells have been cleared so points can be added
    bool atBottom(); //returns true if the cell is at the bottom of the board
    void deactivateScore(); //set potential score to 0
};

#endif
