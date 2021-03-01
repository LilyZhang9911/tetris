#include "block.h"

class L : public Block {
    int pos;
public:
    L(int level, Board *parent);
    bool rotateC();
    bool rotateCC();
};
