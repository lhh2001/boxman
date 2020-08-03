#ifndef INCLUDED_IMAGE_H
#define INCLUDED_IMAGE_H

#include <map>

class Image
{
private:
	int width;
	int height;
	unsigned* data;
	const int gridSize = 32; //一个网格对应像素的数量
	const std::map<char, int> objToImageTable = {
		{'@', 0},
		{'+', 32},
		{'#', 64},
		{'.', 96},
		{' ', 128}
	}; //记录物品在图片中对应的位置

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
