#include "GamePlay.h"
#include "Image.h"
#include "Animation.h"
#include "Boxman.h"
#include <fstream>

GamePlay::GamePlay() : step(0), n(0), m(0) {}

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
    map.clear();
    image.clear();
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

    std::pair<int, int> nowXY(manXY.first + shiftX[dir], manXY.second + shiftY[dir]);
    if (image[nowXY.first][nowXY.second] == ' ' || image[nowXY.first][nowXY.second] == '.') //走一格到空地
    {
        myAnimation = new Animation(manXY, nowXY, dir);
        manXY = nowXY;
        step++;
    }
    else if (image[nowXY.first][nowXY.second] == '#') //碰到箱子
    {
        std::pair<int, int> nowBoxXY(nowXY.first + shiftX[dir], nowXY.second + shiftY[dir]);
        //检查是否可以推着箱子到下一格
        if (image[nowBoxXY.first][nowBoxXY.second] == ' ' || image[nowBoxXY.first][nowBoxXY.second] == '.')
        {
            myAnimation = new Animation(manXY, nowXY, nowBoxXY, dir);
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
            if (image[i][j] != tmp[i][j])
            {
                if (image[i][j] == '@' || tmp[i][j] == '@' && myAnimation != nullptr)
                    continue;
                if (image[i][j] == '#' || tmp[i][j] == '#' && myAnimation != nullptr)
                    continue;
            }
            if (tmp[i][j] != '+')
            {
                gameImage->draw(j, i, ' ');
            }
            if (map[i][j] == '.')
            {
                gameImage->draw(j, i, '.');
            }
            gameImage->draw(j, i, tmp[i][j]);
        }
    }
    image = tmp;
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
