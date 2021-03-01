#ifndef board_h
#define board_h
#include <vector>
#include <string>
#include <memory>
#include "cell.h"
class Level;

class Board {
    std::vector<std::vector<Cell>> board;
    int score;
    std::string file;
    bool specialAvailable; //turns on after clearing over 2 lines
    int heavy;
    bool gameEnd;
    std::unique_ptr<Level> curLevel;
    bool endRound;
    std::shared_ptr <Block> curBlock;
    std::string nextBlock;
    std::vector<std::shared_ptr<Block>> blocks;
    void makeNextBlock(); //generate next block
protected:
    int specialCount;
public:
    Board();
    virtual ~Board();
    void setFile(std::string);
    void levelUp(int n = 1);
    void levelDown(int n = 1);
    Cell* getCell(int x, int y);
    void clearLine(); //clears a full line
    bool checkEnd(std::string type); //returns true if a new block cannot be created, game should end
    void shiftBoard(int row); //shifts everything down starting from row, resets top row
    void nextRound(std::string newblock = ""); //sets current block and makes next block
    void scoreBlock(); //scores the board by checking if each block is deleted
    std::string printrow(int row); //returns a string of the current row
    int getScore();
    int getLevel();
    void changeLevel(int newlevel);
    void resetBlock(std::string type); //used by force to reset curblock
    //moving blocks
    void blockRotateC(int n = 1);
    void blockRotateCC(int n = 1);
    void blockShiftR(int n = 1);
    void blockShiftL(int n = 1);
    bool blockShiftD(int n = 1); //returns whether drop is successful
    void blockDrop();

    std::string printNext();
    std::string printNext(int n);

    bool getSpecial(); //true special actions are available
    void turnoffSpecial();
    virtual void endAction();
    virtual Board * getBoard(); //returns the game board for special actions

    void addHeavy(int n); //adding n drops to heavy
    void subHeavy(int n);

    bool getGameEnd(); //true when new block no longer fits
    bool getEndRound(); //true when the current round ends (heavy results in bottom)
    void turnOffEndRound();
};
#endif

