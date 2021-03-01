#ifndef heavy_
#define heavy_

#include "special.h"

class Heavy : public SpecialAction {
public:
    Heavy(Board * ptr);
    virtual void endAction() override;
};
#endif
