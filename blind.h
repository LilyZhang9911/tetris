#ifndef blind_h
#define blind_h
#include <stdio.h>
#include "special.h"
class Blind: public SpecialAction  {
   public:
    Blind(Board * ptr);
    virtual void endAction() override;
};
#endif

