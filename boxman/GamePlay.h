#ifndef INCLUDED_GAMEPLAY_H
#define INCLUDED_GAMEPLAY_H

#include <vector>
#include <set>
#include <string>

class GamePlay
{
private:
    std::pair<int, int> manXY;            //人的坐标
    std::set<std::pair<int, int>> box;    //箱子坐标
    std::set<std::pair<int, int>> target; //目标坐标
    int n, m;                             //地图的大小
    int step;

public:
    GamePlay();
    GamePlay(std::string input);

    void initMap(std::string input); //初始化地图
    void move(char c);
    void draw();
    bool check();        //检查是否达到胜利的条件
    int getStep() const; //获得任务移动的步数
};

#endif // !INCLUDED_GAMEPLAY_H
