#include "Parent.h" //Sequence::Game::Parent.h
#include "../Parent.h" //Sequence::Parent.h
#include "Loading.h"
#include "Menu.h"
#include "Play.h"
#include "Clear.h"
#include "GameLib/GameLib.h"
#include "../../Animation.h"
#include "../../GamePlay.h"

namespace Sequence
{
	namespace Game
	{
		Parent::Parent(unsigned paramMapID) : loading(nullptr),
			menu(nullptr), play(nullptr),  clear(nullptr),
			myGamePlay(nullptr), myAnimation(nullptr), next(SEQ_NONE)
		{
			mapID = paramMapID;
			loading = new Loading();
		}

		void Parent::update(Sequence::Parent* parent)
		{
			if (loading != nullptr)
			{
				loading->update(this);
			}
			else if (menu != nullptr)
			{
				menu->update(this);
			}
			else if (play != nullptr)
			{
				play->update(this);
			}
			else if (clear != nullptr)
			{
				clear->update(this);
			}

			switch (next)
			{
			case SEQ_TITLE:
				parent->moveTo(Sequence::Parent::SEQ_TITLE);
				break;
			case SEQ_MAP_SELECT:
				parent->moveTo(Sequence::Parent::SEQ_MAP_SELECT);
				break;
			case SEQ_PLAY:
				SAFE_DELETE(loading);
				SAFE_DELETE(menu);
				play = new Play();
				break;
			case SEQ_MENU:
				SAFE_DELETE(play);
				menu = new Menu();
				break;
			case SEQ_LOADING: //重新加载游戏
				SAFE_DELETE(play);
				SAFE_DELETE(menu);
				SAFE_DELETE(myGamePlay);
				map.clear();
				image.clear();
				loading = new Loading();
				break;
			case SEQ_CLEAR:
				SAFE_DELETE(play);
				SAFE_DELETE(menu);
				clear = new Clear();
			default:
				break;
			}
			next = SEQ_NONE;
		}

		void Parent::moveTo(SeqID paramNext)
		{
			next = paramNext;
		}

		Parent::~Parent()
		{
			SAFE_DELETE(loading);
			SAFE_DELETE(menu);
			SAFE_DELETE(play);
			SAFE_DELETE(clear);
			SAFE_DELETE(myGamePlay);
			SAFE_DELETE(myAnimation);
		}
	}
}
