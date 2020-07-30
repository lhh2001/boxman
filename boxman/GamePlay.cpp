#pragma warning(disable:4996)

#include "GamePlay.h"
#include "Image.h"

extern Image* gameImage;

GamePlay::GamePlay() : step(0) {}

GamePlay::GamePlay(std::string input) : step(0)
{
    initMap(input);
    draw();
}

void GamePlay::initMap(std::string input) //初始化地图
{
    input = "maps/" + input + ".txt";
    FILE* fp = fopen(input.c_str(), "r");
    char c;
    fscanf(fp, "%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        map.push_back({});
        image.push_back({});
        //cout << endl;
        for (int j = 0; j < m; j++)
        {
            do
            {
                fscanf(fp, "%c", &c);
            } while (c == '\n');
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
    fclose(fp);
}

bool GamePlay::move(char c)
{
    if (c == 'e')
    {
        return false;
    }
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
        return true;
    }

    std::pair<int, int> nowXY(manXY.first + shiftX[dir], manXY.second + shiftY[dir]);
    if (image[nowXY.first][nowXY.second] == ' ' || image[nowXY.first][nowXY.second] == '.')
    {
        manXY = nowXY;
        step++;
    }
    else if (image[nowXY.first][nowXY.second] == '#')
    {
        std::pair<int, int> nowBoxXY(nowXY.first + shiftX[dir], nowXY.second + shiftY[dir]);
        if (image[nowBoxXY.first][nowBoxXY.second] == ' ' || image[nowBoxXY.first][nowBoxXY.second] == '.')
        {
            manXY = nowXY;
            box.erase(nowXY);
            box.insert(nowBoxXY);
            step++;
        }
    }
    return true;
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
                gameImage->draw(j, i, tmp[i][j]);
            }
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

int GamePlay::getStep()
{
    return step;
}