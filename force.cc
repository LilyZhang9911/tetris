#include "force.h"
#include <iostream>

Force::Force(Board * ptr, std::string block) : SpecialAction(ptr) {
    ++specialCount;
	ptr->resetBlock(block);
}

void Force::endAction() {
}
