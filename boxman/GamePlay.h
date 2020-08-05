#ifndef INCLUDED_GAMEPLAY_H
#define INCLUDED_GAMEPLAY_H

#include <vector>
#include <set>

namespace Sequence
{
    namespace Game
    {
        class Parent;
    }
}

class Image;

class GamePlay
{
private:
    std::pair<int, int> manXY;            //�˵�����
    std::set<std::pair<int, int>> box;    //��������
    std::set<std::pair<int, int>> target; //Ŀ������
    int n, m;                             //��ͼ�Ĵ�С
    int step;
    Sequence::Game::Parent* parent;

public:
    GamePlay();
    ~GamePlay();
    GamePlay(unsigned input, Sequence::Game::Parent* paramParent);

    void initMap(unsigned input); //��ʼ����ͼ
    void move(char c);
    void draw();
    bool check();        //����Ƿ�ﵽʤ��������
    int getStep() const; //��������ƶ��Ĳ���
    Image* gameImage;
};

#endif // !INCLUDED_GAMEPLAY_H
