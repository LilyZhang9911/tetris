#include "level3.h"
#include "board.h"
#include <math.h>
#include "level4.h"
#include "level2.h"

std::string Level3::makeBlock()
{
    int rnd = floor(rand() % 9 + 1);
    switch (rnd)
    {
        case 1: return "O";
        case 2: return "I";
        case 3: return "J";
        case 4: return "L";
        case 5: return "T";
        case 6: case 7: return "S";
        case 8: case 9: return "Z";
    }

    return nullptr;
}

Level3::Level3(Board *boardPtr) : Level(boardPtr, 3) {
    boardPtr->addHeavy(1);
}
