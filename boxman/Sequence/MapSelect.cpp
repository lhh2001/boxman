#include "Parent.h"
#include "MapSelect.h"
#include "GameLib/Framework.h"

namespace Sequence
{
	MapSelect::MapSelect()
	{
		mapSelectImage = new Image("images/mapSelect.dds");
	}

	void MapSelect::update(Parent* parent)
	{
		mapSelectImage->drawEntire();
		for (int i = 1; i <= mapSize; i++)
		{
			if (GameLib::Framework::instance().isKeyTriggered(i + '0'))
			{
				parent->setMapID(i);
				parent->moveTo(Parent::SEQ_GAME);
				break;
			}
		}
	}

	MapSelect::~MapSelect()
	{
		SAFE_DELETE(mapSelectImage);
	}
}
