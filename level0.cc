#include "level0.h"
#include <sstream>

using namespace std;

Level0::Level0(Board* boardPtr, std::string file) : Level(boardPtr, 0), input(fstream{file}) {}

std::string Level0::makeBlock() {
	std::string type;
	if (input >> type) {
		return type;
	}
	else {
		input.clear();
		input.seekg(ios::beg);
		return makeBlock();
	}
}
