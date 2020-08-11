#ifndef INCLUDED_SEQUENCE_GAME_MENU_H
#define INCLUDED_SEQUENCE_GAME_MENU_H

#include "../../Image.h"

namespace Sequence
{
	namespace Game
	{
		class Parent;

		class Menu
		{
		public:
			Menu();
			~Menu();
			void update(Parent* parent);
			static const int selectionSize = 4;

		private:
			Image* menuImage;
			int selection;
		};
	}
}

#endif // !INCLUDED_SEQUENCE_GAME_MENU_H
