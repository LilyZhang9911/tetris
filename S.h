#include "block.h"


class S : public Block {
    int pos;
public:
    S(int level, Board *parent);
    bool rotateC();
    bool rotateCC();
};
