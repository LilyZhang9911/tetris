#ifndef level3_h
#define level3_h

#include "level.h"
class Level;
class Level3 : public Level {
private:
    virtual std::string makeBlock() override;
public:
    Level3(Board *boardPtr);
};
#endif
