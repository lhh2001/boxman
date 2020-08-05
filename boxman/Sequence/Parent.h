#ifndef INCLUDED_SEQUENCE_PARENT_H
#define INCLUDED_SEQUENCE_PARENT_H

namespace Sequence
{
	class Title;
	class MapSelect;
	namespace Game
	{
		class Parent;
	}
	class Parent
	{
	public:
		enum SeqID
		{
			SEQ_TITLE,
			SEQ_MAP_SELECT,
			SEQ_GAME,
			SEQ_NONE
		};
		Parent();
		~Parent();
		void update();
		void moveTo(SeqID);
		void setMapID(unsigned paramMapID);

	private:
		Title* title;
		MapSelect* mapSelect;
		Game::Parent* game;
		SeqID next;
		unsigned mapID;
		const int FPS = 60;
	};
}

#endif // !INCLUDED_SEQUENCE_PARENT_H
