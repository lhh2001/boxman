#include "GameLib/Framework.h"
#include "Image.h"
#include "GamePlay.h"
#include <vector>
#include <set>
#include <string>

using std::vector;
using std::pair;
using std::set;
using std::make_pair;
using std::string;
using namespace GameLib;

bool isInit;
Image* gameImage;
GamePlay* myGame;

namespace GameLib
{
	void Framework::update()
	{
        if (!isInit)
        {
            gameImage = new Image("nimotsuKunImage.dds");
            myGame = new GamePlay("3");
            isInit = true;
        }
        else
        {
            char c;
            cin >> c;
            myGame->move(c);
            myGame->draw();
        }
	}
}

/*
void drawCell(char c, int x, int y)
{
    unsigned* vram = Framework::instance().videoMemory();
    unsigned color = 0;
    int windowWidth = Framework::instance().width();

    switch (c)
    {
    case '+':
        color = 0xffffff;
        break;
    case '#':
        color = 0xff00ff;
        break;
    case '@':
        color = 0x00ffff;
        break;
    case '.':
        color = 0x0000ff;
        break;
    default:
        break;
    }
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            vram[(y * 16 + i) * windowWidth + (x * 16 + j)] = color;
        }
    }
}
*/