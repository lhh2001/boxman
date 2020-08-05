#include "GameLib/GameLib.h"
#include "GameLib/Framework.h"
#include "Parent.h" //Sequence::Parent.h
#include "Title.h"
#include "MapSelect.h"
#include "Game/Parent.h"

namespace Sequence
{
	Parent::Parent() : title(nullptr), mapSelect(nullptr), game(nullptr),
		next(SEQ_NONE)
	{
		title = new Title();
		GameLib::Framework::instance().setFrameRate(FPS);
	}

	void Parent::update()
	{
		if (title != nullptr)
		{
			title->update(this);
		}
		else if (mapSelect != nullptr)
		{
			mapSelect->update(this);
		}
		else if (game != nullptr)
		{
			game->update(this);
		}
		#ifdef _DEBUG
		else
		{
			ASSERT("updateÊ±×´Ì¬¾ùÎª¿Õ");
		}
		#endif // _DEBUG

		switch (next)
		{
		case SEQ_TITLE:
			SAFE_DELETE(game);
			title = new Title();
			break;
		case SEQ_MAP_SELECT:
			SAFE_DELETE(title);
			SAFE_DELETE(game);
			mapSelect = new MapSelect();
			break;
		case SEQ_GAME:
			SAFE_DELETE(mapSelect);
			game = new Game::Parent(mapID);
			break;
		default:
			break;
		}
		next = SEQ_NONE;
	}

	void Parent::moveTo(SeqID paramNext)
	{
		next = paramNext;
	}

	void Parent::setMapID(unsigned paramMapID)
	{
		mapID = paramMapID;
	}

	Parent::~Parent()
	{
		SAFE_DELETE(title);
		SAFE_DELETE(mapSelect);
		SAFE_DELETE(game);
	}
}
