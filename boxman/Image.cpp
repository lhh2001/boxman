#include "GameLib/Framework.h"
#include "Image.h"
#include "File.h"

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

void Image::draw(int x, int y, char object, int shiftX, int shiftY)
{
	unsigned* vram = GameLib::Framework::instance().videoMemory();
	unsigned windowWidth = GameLib::Framework::instance().width();
	int srcX = objToImageTable.find(object)->second;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			int dataIndex = j * width + srcX + i;
			if (data[dataIndex] & 0x80000000)
			{
				vram[(y * gridSize + j + shiftY) * windowWidth + x * gridSize + i + shiftX] = data[dataIndex];
			}
		}
	}
}

int Image::getGridSize() const
{
	return gridSize;
}