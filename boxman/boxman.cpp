#include "GameLib/Framework.h"
#include "Image.h"
#include "GamePlay.h"
#include "Animation.h"
#include "Boxman.h"

using namespace GameLib;

const int INPUT_TYPE_SIZE = 5; //输入按键情况数量
const int INPUT_Q = 4;         //按键Q对应的下标
const int FPS = 60;            //帧率

char inputTable[5] = {
    'a', 's', 'w', 'd', 'q'
};

const int shiftX[4] = { 0, -1, 0, 1 };
const int shiftY[4] = { -1, 0, 1, 0 };

std::vector<std::vector<char>> map;   //存储原始地图, 不包含人和箱子
std::vector<std::vector<char>> image; //上一帧的游戏画面

bool isInit;
bool playerWantToQuit;

Image* gameImage;
GamePlay* myGame;
Animation* myAnimation;

namespace GameLib
{
	void Framework::update()
	{
        cout << frameRate() << endl;
        if (!isInit)
        {
            setFrameRate(FPS);
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
                    SAFE_DELETE(myAnimation);
                }
                return;
            }

            if (myGame->check())
            {
                playerWantToQuit = true;
                GameLib::cout << "恭喜! 您共用"
                    << myGame->getStep() << "步通关!" << GameLib::endl;
            }

            Framework f = Framework::instance();
            for (int i = 0; i < INPUT_TYPE_SIZE; i++)
            {
                if (f.isKeyOn(inputTable[i]))
                {
                    myGame->move(inputTable[i]);
                    myGame->draw();
                    break;
                }
            }
            if (f.isKeyOn(inputTable[INPUT_Q]))
            {
                playerWantToQuit = true;
            }
        }

        if (playerWantToQuit)
        {
            requestEnd();
        }
        if (isEndRequested())
        {
            SAFE_DELETE(myGame);
            SAFE_DELETE(gameImage);

            #ifdef _DEBUG
            map.~vector();
            image.~vector();
            #endif //不提前析构map和image憨憨VS会误报内存泄漏
        }
	}
}
