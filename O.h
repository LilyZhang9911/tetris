#include "block.h"


class O : public Block {
    int pos;
public:
    O(int level, Board *parent);
    bool rotateC();
    bool rotateCC();
};
