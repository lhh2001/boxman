#ifndef INCLUDED_GAMEPLAY_H
#define INCLUDED_GAMEPLAY_H

#include <vector>
#include <set>
#include <string>

class GamePlay
{
private:
    std::vector<std::vector<char>> map;   //�洢ԭʼ��ͼ, �������˺�����
    std::vector<std::vector<char>> image; //��һ֡����Ϸ����
    std::pair<int, int> manXY;       //�˵�����
    std::set<std::pair<int, int>> box;    //��������
    std::set<std::pair<int, int>> target; //Ŀ������
    int n, m;                   //��ͼ�Ĵ�С
    int step;
    const int shiftX[4] = { 0, -1, 0, 1 };
    const int shiftY[4] = { -1, 0, 1, 0 };

public:
    GamePlay();
    GamePlay(std::string input);

    void initMap(std::string input); //��ʼ����ͼ
    bool move(char c);
    void draw();
    bool check();
    int getStep();
};

#endif // !INCLUDED_GAMEPLAY_H
