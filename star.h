#include "block.h"

class Star : public Block {
public:
    Star (int level, Board *parent);
    bool rotateC();
    bool rotateCC();
};

