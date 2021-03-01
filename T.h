#include "block.h"


class T : public Block {
    int pos;
public:
    T(int level, Board *parent);
    bool rotateC();
    bool rotateCC();
};

