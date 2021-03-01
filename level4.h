#ifndef level4_h
#define level4_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "level.h"
class Level;
class Level4 : public Level {
	private:
	    int noClearCount;
		virtual std::string makeBlock() override;
	public:
		Level4(Board *boardPtr);
		void lineCleared();
		virtual Block* checkPenalty();
};
#endif

