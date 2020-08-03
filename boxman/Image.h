#ifndef INCLUDED_IMAGE_H
#define INCLUDED_IMAGE_H

#include <map>

class Image
{
private:
	int width;
	int height;
	unsigned* data;
	const int gridSize = 32; //һ�������Ӧ���ص�����
	const std::map<char, int> objToImageTable = {
		{'@', 0},
		{'+', 32},
		{'#', 64},
		{'.', 96},
		{' ', 128}
	}; //��¼��Ʒ��ͼƬ�ж�Ӧ��λ��

public:
	Image(const char* fileName);
	~Image();
	int getWidth() const;
	int getHeight() const;
	int getGridSize() const;
	void draw(int x, int y, char object, int shiftX = 0, int shiftY = 0);
	void drawEntire();
};

#endif // !INCLUDED_IMAGE_H
