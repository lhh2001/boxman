#ifndef INCLUDED_SEQUENCE_GAME_LOADING_H
#define INCLUDED_SEQUENCE_GAME_LOADING_H

#include "../../Image.h"

namespace Sequence
{
	namespace Game
	{
		class Parent;
		
		class Loading
		{
		private:
			Image* loadingImage;
			bool isStarted;
			bool isImgShown;
			int cnt;

		public:
			Loading();
			~Loading();
			void update(Parent* parent);
		};
	}
}

#endif // !INCLUDED_SEQUENCE_GAME_LOADING_H
