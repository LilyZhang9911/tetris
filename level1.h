#ifndef level1_h
#define level1_h
#include "level.h"

class Level1 : public Level {
private:
    virtual std::string makeBlock() override;
public:
    Level1(Board *boardPtr);
};
#endif


