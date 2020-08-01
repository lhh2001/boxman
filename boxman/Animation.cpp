#include "Animation.h"
#include "Image.h"
#include "boxman.h"

Animation::Animation() : cnt(0), dir(-1) {}

Animation::Animation(vec2 manXY, vec2 nowXY, int paramDir) : cnt(0), dir(paramDir)
{
	background.push_back(manXY);
	background.push_back(nowXY);

	foreground.push_back(manXY);
}

Animation::Animation(vec2 manXY, vec2 nowXY, vec2 nowBoxXY, int paramDir) : cnt(1), dir(paramDir)
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
        gameImage->draw(x, y, ' ');
        if (map[y][x] == '.')
        {
            gameImage->draw(x, y, '.');
        }
    }
    for (auto item : foreground)
    {
        int x = item.second;
        int y = item.first;
        if (image[y + shiftX[dir]][x + shiftY[dir]] == '@')
        {
            gameImage->draw(x, y, '@', shiftY[dir] * cnt, shiftX[dir] * cnt);
        }
        else
        {
            gameImage->draw(x, y, '#', shiftY[dir] * cnt, shiftX[dir] * cnt);
        }
    }
    if (cnt == gameImage->getGridSize())
    {
        return false;
    }
    return true;
}