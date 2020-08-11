#include "Menu.h"
#include "GameLib/Framework.h"
#include "GameLib/GameLib.h"
#include "Parent.h"
#include "../../GamePlay.h"
#include "../../StringRenderer.h"

namespace
{
	const Sequence::Game::Parent::SeqID selectionTable[Sequence::Game::Menu::selectionSize] = {
				Sequence::Game::Parent::SEQ_LOADING,
				Sequence::Game::Parent::SEQ_MAP_SELECT,
				Sequence::Game::Parent::SEQ_TITLE,
				Sequence::Game::Parent::SEQ_PLAY
	};
}

namespace Sequence
{
	namespace Game
	{
		Menu::Menu() : menuImage(nullptr), selection(0)
		{
			menuImage = new Image("images/menu.dds");
		}

		void Menu::update(Parent* parent)
		{
			/*
			0. 重新开始
			1. 回到选关页面
			2. 回到标题页面
			3. 继续游戏
			*/
			GameLib::Framework f = GameLib::Framework::instance();
			if (f.isKeyTriggered('w'))
			{
				if (selection > 0)
				{
					selection--;
				}
			}
			if (f.isKeyTriggered('s'))
			{
				if (selection < selectionSize - 1)
				{
					selection++;
				}
			}
			if (f.isKeyTriggered('f'))
			{
				parent->moveTo(selectionTable[selection]);
			}
			parent->myGamePlay->draw(); //先画前景
			menuImage->drawEntire();    //再画背景
			StringRenderer::getInstance()->draw(1, 2 + selection, ">");
		}

		Menu::~Menu()
		{
			SAFE_DELETE(menuImage);
		}
	}
}
