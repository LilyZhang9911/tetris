#ifndef level2_h
#define level2_h

#include "level.h"
class Level;
class Level2 : public Level {
private:
    virtual std::string makeBlock() override;
public:
    Level2(Board *boardPtr);
};
#endif
