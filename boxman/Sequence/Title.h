#ifndef INCLUDED_SEQUENCE_TITLE_H
#define INCLUDED_SEQUENCE_TITLE_H

#include "../Image.h"

namespace Sequence
{
	class Parent;
	class Title
	{
	private:
		Image* titleImage;

	public:
		Title();
		~Title();
		void update(Parent* parent);
	};
}

#endif // !INCLUDED_SEQUENCE_TITLE_H
