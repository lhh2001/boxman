#include "GamePlay.h"
#include "Image.h"
#include <fstream>

extern Image* gameImage;

GamePlay::GamePlay() : step(0), n(0), m(0), animeCnt(0), animeDir(-1) {}

GamePlay::GamePlay(std::string input) : step(0)
{
    initMap(input);
    draw();
}

void GamePlay::initMap(std::string input) //初始化地图
{
    input = "maps/" + input + ".txt";
    std::ifstream f(input, std::ifstream::binary);
    char c;
    f >> n >> m;
    for (int i = 0; i < n; i++)
    {
        map.push_back({});
        image.push_back({});
        for (int j = 0; j < m; j++)
        {
            do
            {
               c = f.get();
            } while (c == '\n' || c == '\r');
            //GameLib::cout << c;
            map[i].push_back(c);
            image[i].push_back('\0');
            if (map[i][j] == '@')
            {
                manXY = std::make_pair(i, j);
                map[i][j] = ' ';
            }
            else if (map[i][j] == '#')
            {
                box.insert(std::make_pair(i, j));
                map[i][j] = ' ';
            }
            else if (map[i][j] == '.')
            {
                target.insert(std::make_pair(i, j));
            }
        }
        //GameLib::cout << GameLib::endl;
    }
    f.close();
}

void GamePlay::move(char c)
{
    int dir = -1;
    switch (c)
    {
    case 'a':
        dir = 0; //左
        break;
    case 'w':
        dir = 1; //上
        break;
    case 'd':
        dir = 2; //右
        break;
    case 's':
        dir = 3; //下
        break;
    }
    if (dir == -1)
    {
        return;
    }

    std::pair<int, int> nowXY(manXY.first + shiftX[dir], manXY.second + shiftY[dir]);
    if (image[nowXY.first][nowXY.second] == ' ' || image[nowXY.first][nowXY.second] == '.')
    {
        animeBackground.clear();
        animeBackground.push_back(manXY);
        animeBackground.push_back(nowXY);

        animeForeground.clear();
        animeForeground.push_back(manXY);

        animeDir = dir;
        animeCnt = 1;

        manXY = nowXY;
        step++;
    }
    else if (image[nowXY.first][nowXY.second] == '#')
    {
        std::pair<int, int> nowBoxXY(nowXY.first + shiftX[dir], nowXY.second + shiftY[dir]);
        if (image[nowBoxXY.first][nowBoxXY.second] == ' ' || image[nowBoxXY.first][nowBoxXY.second] == '.')
        {
            animeBackground.clear();
            animeBackground.push_back(manXY);
            animeBackground.push_back(nowXY);
            animeBackground.push_back(nowBoxXY);

            animeForeground.clear();
            animeForeground.push_back(manXY);
            animeForeground.push_back(nowXY);

            animeDir = dir;
            animeCnt = 1;

            manXY = nowXY;
            box.erase(nowXY);
            box.insert(nowBoxXY);
            step++;
        }
    }
}

void GamePlay::draw()
{
    std::vector<std::vector<char>> tmp = map;
    auto iter = box.begin();
    while (iter != box.end())
    {
        tmp[iter->first][iter->second] = '#';
        iter++;
    }
    tmp[manXY.first][manXY.second] = '@';
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (tmp[i][j] != image[i][j])
            {
                if (tmp[i][j] != '+')
                {
                    gameImage->draw(j, i, ' ');
                }
                if (image[i][j] == '.')
                {
                    gameImage->draw(j, i, '.');
                }
                gameImage->draw(j, i, tmp[i][j]);
            }
        }
    }
    image = tmp;
    
    if (animeCnt)
    {
        for (auto item : animeBackground)
        {
            int x = item.second;
            int y = item.first;
            gameImage->draw(x, y, ' ');
            if (map[y][x] == '.')
            {
                gameImage->draw(x, y, '.');
            }
        }
        for (auto item : animeForeground)
        {
            int x = item.second;
            int y = item.first;
            if (image[y + shiftX[animeDir]][x + shiftY[animeDir]] == '@')
            {
                gameImage->draw(x, y, '@', shiftY[animeDir] * animeCnt, shiftX[animeDir] * animeCnt);
            }
            else
            {
                gameImage->draw(x, y, '#', shiftY[animeDir] * animeCnt, shiftX[animeDir] * animeCnt);
            }
        }
        if (animeCnt == gameImage->getGridSize())
        {
            animeCnt = 0;
            return;
        }
        animeCnt++;
    }
}

bool GamePlay::check()
{
    if (box == target)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int GamePlay::getStep() const
{
    return step;
}

int GamePlay::getAnimeCnt() const
{
    return animeCnt;
}
