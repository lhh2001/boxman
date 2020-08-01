#ifndef INCLUDED_GAMEPLAY_H
#define INCLUDED_GAMEPLAY_H

#include <vector>
#include <set>
#include <string>

class GamePlay
{
private:
    std::vector<std::vector<char>> map;   //存储原始地图, 不包含人和箱子
    std::vector<std::vector<char>> image; //上一帧的游戏画面
    std::pair<int, int> manXY;       //人的坐标
    std::set<std::pair<int, int>> box;    //箱子坐标
    std::set<std::pair<int, int>> target; //目标坐标
    int n, m;                   //地图的大小
    int step;
    const int shiftX[4] = { 0, -1, 0, 1 };
    const int shiftY[4] = { -1, 0, 1, 0 };

    std::vector<std::pair<int, int>> animeBackground; //存储动画播放的背景(不移动的物体)
    std::vector<std::pair<int, int>> animeForeground; //存储动画需要移动的物体
    int animeCnt; //动画已经播放的帧数
    int animeDir; //动画来时的方向

public:
    GamePlay();
    GamePlay(std::string input);

    void initMap(std::string input); //初始化地图
    void move(char c);
    void draw();
    bool check();
    int getStep() const;
    int getAnimeCnt() const;
};

#endif // !INCLUDED_GAMEPLAY_H
