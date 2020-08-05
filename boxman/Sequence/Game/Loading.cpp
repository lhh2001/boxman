#include "Loading.h"
#include "Parent.h" //Sequence::Game::Parent.h
#include "GameLib/GameLib.h"
#include "../../GamePlay.h"

namespace Sequence
{
	namespace Game
	{
		Loading::Loading() : isStarted(false), cnt(0),
			loadingImage(nullptr), isImgShown(false)
		{
			loadingImage = new Image("images/loading.dds");
		}

		void Loading::update(Parent* parent)
		{
			if (!isImgShown)
			{
				loadingImage->drawEntire();
				isImgShown = true;
			}
			else
			{
				if (!isStarted)
				{
					parent->myGamePlay = new GamePlay(parent->mapID, parent);
					isStarted = true;
				}
			}

			if (isStarted && cnt >= 60)
			{
				parent->moveTo(Parent::SEQ_PLAY);
			}
			cnt++;
		}

		Loading::~Loading()
		{
			SAFE_DELETE(loadingImage);
		}
	}
}
