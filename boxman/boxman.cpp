#include "GameLib/Framework.h"
#include <vector>
#include <set>
#include <string>

#pragma warning(disable:4996)

using std::vector;
using std::pair;
using std::set;
using std::make_pair;
using std::string;
using namespace GameLib;

namespace GameLib
{
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
    
    class Game
    {
    private:
        vector<vector<char>> map;   //存储原始地图, 不包含人和箱子
        vector<vector<char>> image; //上一帧的游戏画面
        pair<int, int> manXY;       //人的坐标
        set<pair<int, int>> box;    //箱子坐标
        set<pair<int, int>> target; //目标坐标
        int n, m;                   //地图的大小
        int step;
        const int shiftX[4] = { 0, -1, 0, 1 };
        const int shiftY[4] = { -1, 0, 1, 0 };

    public:
        Game() : step(0) {}
        Game(string input) : step(0)
        {
            initMap(input);
            //draw();
        }

        void initMap(string input) //初始化地图
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
                    image[i].push_back(' ');
                    if (map[i][j] == '@')
                    {
                        manXY = make_pair(i, j);
                        map[i][j] = ' ';
                    }
                    else if (map[i][j] == '#')
                    {
                        box.insert(make_pair(i, j));
                        map[i][j] = ' ';
                    }
                    else if (map[i][j] == '.')
                    {
                        target.insert(make_pair(i, j));
                    }
                }
            }
            fclose(fp);
        }

        bool move(char c)
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

            pair<int, int> nowXY(manXY.first + shiftX[dir], manXY.second + shiftY[dir]);
            if (image[nowXY.first][nowXY.second] == ' ' || image[nowXY.first][nowXY.second] == '.')
            {
                manXY = nowXY;
                step++;
            }
            else if (image[nowXY.first][nowXY.second] == '#')
            {
                pair<int, int> nowBoxXY(nowXY.first + shiftX[dir], nowXY.second + shiftY[dir]);
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

        void draw()
        {
            vector<vector<char>> tmp = map;
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
                        drawCell(tmp[i][j], j, i);
                    }
                }
            }
            image = tmp;
        }

        bool check()
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

        int getStep()
        {
            return step;
        }
    };

    Game myGame("1");

	void Framework::update()
	{
        char c;
        cin >> c;
        myGame.move(c);
        myGame.draw();
	}
}