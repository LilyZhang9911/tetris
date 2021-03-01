#include "heavy.h"
#include <iostream>


Heavy::Heavy(Board * ptr) : SpecialAction(ptr) {
    ++specialCount;
    board->addHeavy(2);
}

void Heavy::endAction() {
    board->subHeavy(2);
}
