#ifndef INCLUDED_GAMEPLAY_H
#define INCLUDED_GAMEPLAY_H

#include <vector>
#include <set>
#include <string>

class GamePlay
{
private:
    std::pair<int, int> manXY;            //�˵�����
    std::set<std::pair<int, int>> box;    //��������
    std::set<std::pair<int, int>> target; //Ŀ������
    int n, m;                             //��ͼ�Ĵ�С
    int step;

public:
    GamePlay();
    GamePlay(std::string input);

    void initMap(std::string input); //��ʼ����ͼ
    void move(char c);
    void draw();
    bool check();        //����Ƿ�ﵽʤ��������
    int getStep() const; //��������ƶ��Ĳ���
};

#endif // !INCLUDED_GAMEPLAY_H
