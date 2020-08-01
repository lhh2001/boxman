#ifndef INCLUDED_ANIMATION_H
#define INCLUDED_ANIMATION_H

#include <vector>

typedef std::pair<int, int> vec2;

class Animation
{
private:
	std::vector<vec2> background; //存储动画播放的背景(不移动的物体)
	std::vector<vec2> foreground; //存储动画需要移动的物体
	int cnt; //动画已经播放的帧数
	int dir; //动画来时的方向

public:
	Animation();
	Animation(vec2 manXY, vec2 nowXY, int paramDir);
	Animation(vec2 manXY, vec2 nowXY, vec2 nowBoxXY, int paramDir);
	bool draw(); //return false表示动画已经播放完毕
};

#endif // !INCLUDED_ANIMATION_H

