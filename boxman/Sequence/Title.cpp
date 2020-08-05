#include "Title.h"
#include "GameLib/Framework.h"
#include "Parent.h"

namespace Sequence
{
	Title::Title()
	{
		titleImage = new Image("images/title.dds");
	}

	void Title::update(Parent* parent)
	{
		titleImage->drawEntire();
		if (GameLib::Framework::instance().isKeyTriggered(' '))
		{
			parent->moveTo(Parent::SEQ_MAP_SELECT);
		}
	}

	Title::~Title()
	{
		SAFE_DELETE(titleImage);
	}
}
