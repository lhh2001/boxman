#include "Play.h"
#include "GameLib/Framework.h"
#include "Parent.h"
#include "../../Animation.h"
#include "../../GamePlay.h"

namespace Sequence
{
	namespace Game
	{
		Play::Play() {}
		Play::~Play() {}
		void Play::update(Parent* parent)
		{
			GameLib::Framework f = GameLib::Framework::instance();
            if (parent->myAnimation != nullptr)
            {
                if (!parent->myAnimation->draw())
                {
                    SAFE_DELETE(parent->myAnimation);
                }
                return;
            }

            if (parent->myGamePlay->check())
            {
                GameLib::cout << "恭喜! 您共用"
                    << parent->myGamePlay->getStep() << "步通关!" << GameLib::endl;
                parent->moveTo(Parent::SEQ_CLEAR);
                return;
            }
            for (int i = 0; i < INPUT_TYPE_SIZE; i++)
            {
                if (f.isKeyOn(inputTable[i]))
                {
                    parent->myGamePlay->move(inputTable[i]);
                    break;
                }
            }
            if (f.isKeyOn(' '))
            {
                parent->moveTo(Parent::SEQ_MENU);
            }
            parent->myGamePlay->draw();
		}
	}
}
