#include "Clear.h"
#include "../../Image.h"
#include "Parent.h"
#include "../../GamePlay.h"
#include "GameLib/GameLib.h"
#include "../../StringRenderer.h"
#include <sstream>

namespace Sequence
{
	namespace Game
	{
		Clear::Clear() : clearImage(nullptr), cnt(0)
		{
			clearImage = new Image("images/clear.dds");
			clearImage->drawEntire();
		}

		void Clear::update(Parent* parent)
		{
			if (cnt == 0)
			{
				step = std::to_string(parent->myGamePlay->getStep());
			}
			if (cnt >= 90)
			{
				parent->moveTo(Parent::SEQ_TITLE);
			}
			StringRenderer::getInstance()->draw(23, 8, step.c_str(), 0xfb266c);
			cnt++;
		}

		Clear::~Clear()
		{
			SAFE_DELETE(clearImage);
		}
	}
}
