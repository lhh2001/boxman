#ifndef INCLUDED_SEQUENCE_GAME_PARENT_H
#define INCLUDED_SEQUENCE_GAME_PARENT_H

#include <vector>

class GamePlay;
class Animation;

namespace Sequence
{
	class Parent;

	namespace Game
	{
		class Loading;
		class Menu;
		class Play;
		
		class Parent
		{
		public:
			enum SeqID
			{
				SEQ_TITLE,
				SEQ_MAP_SELECT,
				SEQ_LOADING,
				SEQ_MENU,
				SEQ_PLAY,
				SEQ_NONE
			};
			GamePlay* myGamePlay; //��Ϸ����
			Animation* myAnimation;
			std::vector<std::vector<char>> map;   //�洢ԭʼ��ͼ, �������˺�����
			std::vector<std::vector<char>> image; //��һ֡����Ϸ����
			const int shiftX[4] = { 0, -1, 0, 1 };
			const int shiftY[4] = { -1, 0, 1, 0 };
			unsigned mapID;

			Parent(unsigned paramMapID);
			~Parent();
			void update(Sequence::Parent* parent);
			void moveTo(SeqID);

		private:
			Loading* loading;
			Menu* menu;
			Play* play;
			SeqID next;
		};
	}
}

#endif // !INCLUDED_SEQUENCE_GAME_PARENT_H
