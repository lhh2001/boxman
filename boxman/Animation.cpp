#include "Animation.h"
#include "Image.h"
#include "Sequence/Game/Parent.h"
#include "GamePlay.h"

Animation::Animation() : cnt(0), dir(-1) {}

Animation::Animation(vec2 manXY, vec2 nowXY, int paramDir, Sequence::Game::Parent* paramParent)
    : cnt(0), dir(paramDir), parent(paramParent)
{
	background.push_back(manXY);
	background.push_back(nowXY);

	foreground.push_back(manXY);
}

Animation::Animation(vec2 manXY, vec2 nowXY, vec2 nowBoxXY, int paramDir, Sequence::Game::Parent* paramParent)
    : cnt(1), dir(paramDir), parent(paramParent)
{
	background.push_back(manXY);
	background.push_back(nowXY);
	background.push_back(nowBoxXY);

	foreground.push_back(manXY);
	foreground.push_back(nowXY);
}

bool Animation::draw()
{
    cnt++;
    for (auto item : background)
    {
        int x = item.second;
        int y = item.first;
        parent->myGamePlay->gameImage->draw(x, y, ' ');
        if (parent->map[y][x] == '.')
        {
            parent->myGamePlay->gameImage->draw(x, y, '.');
        }
    }
    for (auto item : foreground)
    {
        int x = item.second;
        int y = item.first;
        if (parent->image[y + parent->shiftX[dir]][x + parent->shiftY[dir]] == '@')
        {
            parent->myGamePlay->gameImage->draw(x, y, '@', parent->shiftY[dir] * cnt, parent->shiftX[dir] * cnt);
        }
        else
        {
            parent->myGamePlay->gameImage->draw(x, y, '#', parent->shiftY[dir] * cnt, parent->shiftX[dir] * cnt);
        }
    }
    if (cnt == parent->myGamePlay->gameImage->getGridSize())
    {
        return false;
    }
    return true;
}
