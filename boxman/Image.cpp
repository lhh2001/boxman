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
			int vramIndex = (y * gridSize + j + shiftY) * windowWidth + x * gridSize + i + shiftX;
			unsigned src = data[dataIndex];
			unsigned dst = vram[vramIndex];

			unsigned srcA = (src & 0xff000000) >> 24;
			unsigned srcR = (src & 0x00ff0000);
			unsigned srcG = (src & 0x0000ff00);
			unsigned srcB = (src & 0x000000ff);

			unsigned dstR = (dst & 0x00ff0000);
			unsigned dstG = (dst & 0x0000ff00);
			unsigned dstB = (dst & 0x000000ff);

			unsigned r = (srcR - dstR) * srcA / 255 + dstR;
			unsigned g = (srcG - dstG) * srcA / 255 + dstG;
			unsigned b = (srcB - dstB) * srcA / 255 + dstB;

			vram[vramIndex] = (r & 0xff0000) | (g & 0x0000ff00) | b;
		}
	}
}

void Image::drawEntire()
{
	unsigned* vram = GameLib::Framework::instance().videoMemory();
	unsigned windowWidth = GameLib::Framework::instance().width();
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			int dataIndex = j * width + i;
			int vramIndex = j * windowWidth + i;
			unsigned src = data[dataIndex];
			unsigned dst = vram[vramIndex];

			unsigned srcA = (src & 0xff000000) >> 24;
			unsigned srcR = (src & 0x00ff0000);
			unsigned srcG = (src & 0x0000ff00);
			unsigned srcB = (src & 0x000000ff);

			unsigned dstR = (dst & 0x00ff0000);
			unsigned dstG = (dst & 0x0000ff00);
			unsigned dstB = (dst & 0x000000ff);

			unsigned r = (srcR - dstR) * srcA / 255 + dstR;
			unsigned g = (srcG - dstG) * srcA / 255 + dstG;
			unsigned b = (srcB - dstB) * srcA / 255 + dstB;

			vram[vramIndex] = (r & 0xff0000) | (g & 0x0000ff00) | b;
		}
	}
}

int Image::getGridSize() const
{
	return gridSize;
}
