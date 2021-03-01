#ifndef level0_h
#define level0_h
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "level.h"


class Level0 : public Level {
	private:
		std::fstream input;
		virtual std::string makeBlock() override;
	public:
		Level0(Board* boardPtr, std::string file);
		/*
		virtual void addClearNum() override;
		virtual Level* nextLevel() override;
		virtual Level* previousLevel() override; */
};

#endif
