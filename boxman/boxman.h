#pragma once

class Image;
class GamePlay;
class Animaiton;

extern const int shiftX[4];
extern const int shiftY[4];

extern std::vector<std::vector<char>> map;   //�洢ԭʼ��ͼ, �������˺�����
extern std::vector<std::vector<char>> image; //��һ֡����Ϸ����

extern Image* gameImage;
extern GamePlay* myGame;
extern Animation* myAnimation;

