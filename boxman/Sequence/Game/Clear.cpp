#include "Clear.h"
#include "../../Image.h"
#include "Parent.h"
#include "GameLib/GameLib.h"
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
			if (cnt >= 90)
			{
				parent->moveTo(Parent::SEQ_TITLE);
			}
			cnt++;
		}

		Clear::~Clear()
		{
			SAFE_DELETE(clearImage);
		}
	}
}
