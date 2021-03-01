#ifndef specialAction_
#define specialAction_

#include "board.h"

class SpecialAction : public Board {
	protected:
		Board* board;
	public:
		SpecialAction(Board* ptr);
        virtual ~SpecialAction();
		virtual Board *getBoard() override;
        virtual void endAction() = 0;
};
#endif
