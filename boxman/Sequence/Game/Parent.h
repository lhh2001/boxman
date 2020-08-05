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
			GamePlay* myGamePlay; //游戏主体
			Animation* myAnimation;
			std::vector<std::vector<char>> map;   //存储原始地图, 不包含人和箱子
			std::vector<std::vector<char>> image; //上一帧的游戏画面
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
