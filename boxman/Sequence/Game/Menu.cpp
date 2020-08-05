#include "Menu.h"
#include "GameLib/Framework.h"
#include "GameLib/GameLib.h"
#include "Parent.h"
#include "../../GamePlay.h"

namespace Sequence
{
	namespace Game
	{
		Menu::Menu() : menuImage(nullptr)
		{
			menuImage = new Image("images/menu.dds");
		}

		void Menu::update(Parent* parent)
		{
			/*
			1. 重新开始
			2. 选关
			3. 转到标题画面
			4. 返回
			*/
			parent->myGamePlay->draw(); //先画前景
			menuImage->drawEntire();    //再画背景
			GameLib::Framework f = GameLib::Framework::instance();
			for (int i = 1; i <= selectionSize; i++)
			{
				if (f.isKeyTriggered('1')) //重新开始
				{
					parent->moveTo(Parent::SEQ_LOADING);
				}
				else if (f.isKeyTriggered('2'))
				{
					parent->moveTo(Parent::SEQ_MAP_SELECT);
				}
				else if (f.isKeyTriggered('3'))
				{
					parent->moveTo(Parent::SEQ_TITLE);
				}
				else if (f.isKeyTriggered('4'))
				{
					parent->moveTo(Parent::SEQ_PLAY);
				}
			}
		}

		Menu::~Menu()
		{
			SAFE_DELETE(menuImage);
		}
	}
}
