#ifndef INCLUDED_ANIMATION_H
#define INCLUDED_ANIMATION_H

#include <vector>

typedef std::pair<int, int> vec2;

class Animation
{
private:
	std::vector<vec2> background; //�洢�������ŵı���(���ƶ�������)
	std::vector<vec2> foreground; //�洢������Ҫ�ƶ�������
	int cnt; //�����Ѿ����ŵ�֡��
	int dir; //������ʱ�ķ���

public:
	Animation();
	Animation(vec2 manXY, vec2 nowXY, int paramDir);
	Animation(vec2 manXY, vec2 nowXY, vec2 nowBoxXY, int paramDir);
	bool draw(); //return false��ʾ�����Ѿ��������
};

#endif // !INCLUDED_ANIMATION_H

