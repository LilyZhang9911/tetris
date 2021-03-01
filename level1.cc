#include "level1.h"
#include "board.h"
#include <cstdlib>
#include <math.h>
using namespace std;

std::string Level1::makeBlock() {
    int rnd = floor(rand() % 12 + 1);
    switch (rnd) {
        case 1: return "S";
        case 2: return "Z";
        case 3: case 10: return "J";
        case 4: case 11: return "L";
        case 5: case 12: return "T";
        case 6: case 7: return "O";
        case 8: case 9: return "I";
    }
    return nullptr;
}

Level1::Level1(Board *boardPtr) : Level{boardPtr, 1} {}
