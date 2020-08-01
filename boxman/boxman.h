#pragma once

class Image;
class GamePlay;
class Animaiton;

extern const int shiftX[4];
extern const int shiftY[4];

extern std::vector<std::vector<char>> map;   //存储原始地图, 不包含人和箱子
extern std::vector<std::vector<char>> image; //上一帧的游戏画面

extern Image* gameImage;
extern GamePlay* myGame;
extern Animation* myAnimation;

