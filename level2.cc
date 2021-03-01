#include "level2.h"
#include "board.h"
#include <math.h>
using namespace std;

std::string Level2::makeBlock()
{
    int rnd = floor(rand() % 7 + 1);
    switch (rnd)
    {
        case 1: return "S";
        case 2: return "Z";
        case 3: return "J";
        case 4: return "L";
        case 5: return "T";
        case 6: return "O";
        case 7: return "I";
    }

    return nullptr;
}

Level2::Level2(Board *boardPtr) : Level(boardPtr, 2) {}
