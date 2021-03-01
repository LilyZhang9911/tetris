#include "block.h"


class Z : public Block {
    int pos;
public:
    Z(int level, Board *parent);
    bool rotateC();
    bool rotateCC();
};

