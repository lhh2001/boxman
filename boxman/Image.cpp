#include "GameLib/Framework.h"
#include "Image.h"
#include "File.h"

const int gridSize = 32; //一个网格对应像素的数量

const std::map<char, int> objToImageTable = {
	{'@', 0},
	{'+', 32},
	{'#', 64},
	{'.', 128},
	{' ', 160}
}; //记录物品在图片中对应的位置

Image::Image(const char* fileName) : width(0), height(0), data(nullptr)
{
	File f(fileName);
	if (f.getData() != nullptr)
	{
		unsigned dwMagic = f.getUnsigned(0);
		if (dwMagic == ('D' | ('D' << 8) | ('S' << 16) | (' ' << 24)))
		{
			width = f.getUnsigned(16);
			height = f.getUnsigned(12);
			data = new unsigned[width * height];
			for (int i = 0; i < width * height; i++)
			{
				data[i] = f.getUnsigned(128 + i * 4);
			}
		}
	}
}

Image::~Image()
{
	delete[] data;
	data = nullptr;
}

int Image::getWidth() const
{
	return width;
}

int Image::getHeight() const
{
	return height;
}

void Image::draw(int x, int y, char object)
{
	unsigned* vram = GameLib::Framework::instance().videoMemory();
	unsigned windowWidth = GameLib::Framework::instance().width();
	int srcX = objToImageTable.find(object)->second;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			vram[(y * gridSize + j) * windowWidth + x * gridSize + i] = data[j * width + srcX + i];
		}
	}
}