#ifndef level_h
#define level_h
#include <vector>
#include <string>

class Board;
class Block;

class Level{
	private:
		int level;
    protected:
        Board *board;
        Level(Board *boardPtr, int level); //constructor
	public:
	    virtual ~Level();
	    virtual std::string makeBlock() = 0; //each level creates a different type of block
        Block* activate(std::string type); //activate a given block by placing it on board
		int getLevel(); //level getter
		Level *changeLevel(int newlevel, std::string file = ""); //change level to specified
        virtual Block* checkPenalty();
        virtual void lineCleared();
};
#endif

