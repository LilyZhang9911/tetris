#include "block.h"


class J : public Block {
    int pos;
public:
    J(int level, Board *parent);
    bool rotateC();
    bool rotateCC();
};
