#include "GameLib/Framework.h"
#include "Image.h"
#include "GamePlay.h"
#include "Animation.h"
#include "boxman.h"

using namespace GameLib;

const int INPUT_TYPE_SIZE = 5; //输入按键情况数量
const int INPUT_Q = 4;         //按键Q对应的下标

char inputTable[5] = {
    'a', 's', 'w', 'd', 'q'
};

const int shiftX[4] = { 0, -1, 0, 1 };
const int shiftY[4] = { -1, 0, 1, 0 };

std::vector<std::vector<char>> map;   //存储原始地图, 不包含人和箱子
std::vector<std::vector<char>> image; //上一帧的游戏画面

bool isInit;
bool playerWantToQuit;
bool prevInput[INPUT_TYPE_SIZE]; //判断上一帧对应按键是否被按下

Image* gameImage;
GamePlay* myGame;
Animation* myAnimation;

namespace GameLib
{
	void Framework::update()
	{
        if (!isInit)
        {
            myAnimation = nullptr;
            gameImage = new Image("nimotsuKunImage2.dds");
            myGame = new GamePlay("3");
            isInit = true;
        }
        else
        {
            if (myAnimation != nullptr)
            {
                if (!myAnimation->draw())
                {
                    delete myAnimation;
                    myAnimation = nullptr;
                }
                return;
            }
            bool nowInput[INPUT_TYPE_SIZE] = { false };
            Framework f = Framework::instance();
            for (int i = 0; i < INPUT_TYPE_SIZE; i++)
            {
                nowInput[i] = f.isKeyOn(inputTable[i]);
                if (nowInput[i] && !prevInput[i])
                {
                    myGame->move(inputTable[i]);
                    myGame->draw();
                }
                prevInput[i] = nowInput[i];
            }
            if (nowInput[INPUT_Q])
            {
                playerWantToQuit = true;
            }
        }

        if (myGame->check())
        {
            playerWantToQuit = true;
            GameLib::cout << "恭喜! 您共用" 
                << myGame->getStep() << "步通关!" << GameLib::endl;
        }

        if (playerWantToQuit)
        {
            requestEnd();
        }
        if (isEndRequested())
        {
            delete myGame;
            delete gameImage;
        }
	}
}
