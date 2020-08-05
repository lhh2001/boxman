#include "GamePlay.h"
#include "Image.h"
#include "Animation.h"
#include <fstream>
#include <sstream>
#include "Image.h"
#include "Sequence/Game/Parent.h"
#include "GameLib/GameLib.h"

GamePlay::GamePlay() : step(0), n(0), m(0) {}

GamePlay::GamePlay(unsigned input, Sequence::Game::Parent* paramParent) : step(0)
{
    parent = paramParent;
    initMap(input);
    gameImage = new Image("images/nimotsuKunImage2.dds");
}

void GamePlay::initMap(unsigned input) //初始化地图
{
    std::ostringstream fileName;
    fileName << "maps/" << input << ".txt";
    std::ifstream f(fileName.str(), std::ifstream::binary);
    char c;
    f >> n >> m;
    parent->map.clear();
    parent->image.clear();
    for (int i = 0; i < n; i++)
    {
        parent->map.push_back({});
        parent->image.push_back({});
        for (int j = 0; j < m; j++)
        {
            do
            {
               c = f.get();
            } while (c == '\n' || c == '\r');
            parent->map[i].push_back(c);
            parent->image[i].push_back('\0');
            if (parent->map[i][j] == '@')
            {
                manXY = std::make_pair(i, j);
                parent->map[i][j] = ' ';
            }
            else if (parent->map[i][j] == '#')
            {
                box.insert(std::make_pair(i, j));
                parent->map[i][j] = ' ';
            }
            else if (parent->map[i][j] == '.')
            {
                target.insert(std::make_pair(i, j));
            }
        }
    }
    f.close();
}

void GamePlay::move(char c)
{
    static const std::map<char, int> dirTable = {
        {'a', 0}, {'w', 1}, {'d', 2}, {'s', 3} //左 上 右 下
    };
    auto iter = dirTable.find(c);
    if (iter == dirTable.end())
    {
        return;
    }
    int dir = iter->second;

    std::pair<int, int> nowXY(manXY.first + parent->shiftX[dir], manXY.second + parent->shiftY[dir]);
    if (parent->image[nowXY.first][nowXY.second] == ' ' || parent->image[nowXY.first][nowXY.second] == '.') //走一格到空地
    {
        parent->myAnimation = new Animation(manXY, nowXY, dir, parent);
        manXY = nowXY;
        step++;
    }
    else if (parent->image[nowXY.first][nowXY.second] == '#') //碰到箱子
    {
        std::pair<int, int> nowBoxXY(nowXY.first + parent->shiftX[dir], nowXY.second + parent->shiftY[dir]);
        //检查是否可以推着箱子到下一格
        if (parent->image[nowBoxXY.first][nowBoxXY.second] == ' ' || parent->image[nowBoxXY.first][nowBoxXY.second] == '.')
        {
            parent->myAnimation = new Animation(manXY, nowXY, nowBoxXY, dir, parent);
            manXY = nowXY;
            box.erase(nowXY);
            box.insert(nowBoxXY);
            step++;
        }
    }
}

void GamePlay::draw()
{
    std::vector<std::vector<char>> tmp = parent->map;
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
            if (parent->image[i][j] != tmp[i][j])
            {
                if (parent->image[i][j] == '@' || tmp[i][j] == '@' && parent->myAnimation != nullptr)
                    continue;
                if (parent->image[i][j] == '#' || tmp[i][j] == '#' && parent->myAnimation != nullptr)
                    continue;
            }
            if (tmp[i][j] != '+')
            {
                gameImage->draw(j, i, ' ');
            }
            if (parent->map[i][j] == '.')
            {
                gameImage->draw(j, i, '.');
            }
            gameImage->draw(j, i, tmp[i][j]);
        }
    }
    parent->image = tmp;
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

GamePlay::~GamePlay()
{
    SAFE_DELETE(gameImage);
}