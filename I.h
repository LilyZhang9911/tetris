#include "block.h"


class I : public Block {
    int pos;
public:
    I(int level, Board *parent);
    bool rotateC();
    bool rotateCC();
};
