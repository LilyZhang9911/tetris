#ifndef force_
#define force__

#include "special.h"
class Force : public SpecialAction {
public:
    Force(Board * ptr, std::string block);
    virtual void endAction() override;
};

#endif
