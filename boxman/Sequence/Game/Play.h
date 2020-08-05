#ifndef INCLUDED_SEQUENCE_GAME_PLAY_H
#define INCLUDED_SEQUENCE_GAME_PLAY_H

namespace Sequence
{
	namespace Game
	{
		class Parent;

		class Play
		{
		public:
			Play();
			~Play();
			void update(Parent* parent);

		private:
			const int INPUT_TYPE_SIZE = 5; //输入按键情况数量
			const int INPUT_Q = 4;         //按键Q对应的下标
			const char inputTable[5] = {
				'a', 's', 'w', 'd', 'q'
			};
		};
	}
}

#endif // !INCLUDED_SEQUENCE_GAME_PLAY_H
