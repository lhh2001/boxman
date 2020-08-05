#ifndef INCLUDED_SEQUENCE_MAPSELECT_H
#define INCLUDED_SEQUENCE_MAPSELECT_H

#include "../Image.h"

namespace Sequence
{
	class Parent;

	class MapSelect
	{
	private:
		Image* mapSelectImage;
		const int mapSize = 3; //µÿÕº¥Û–°

	public:
		MapSelect();
		~MapSelect();
		void update(Parent* parent);
	};
}

#endif // !INCLUDED_SEQUENCE_MAPSELECT_H
