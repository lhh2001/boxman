#include "StringRenderer.h"
#include "Image.h"
#include "GameLib/Framework.h"

StringRenderer* StringRenderer::instance = nullptr;

void StringRenderer::create(const char* fileName)
{
	STRONG_ASSERT(!(instance != nullptr) && "不允许创建两个对象!");
	instance = new StringRenderer(fileName);
}

void StringRenderer::destroy()
{
	STRONG_ASSERT(!(instance == nullptr) && "不允许执行两次析构!");
	instance->~StringRenderer();
}

StringRenderer::StringRenderer(const char* fileName) : fontImage(nullptr)
{
	fontImage = new Image(fileName);
}

StringRenderer::~StringRenderer()
{
	SAFE_DELETE(fontImage);
}

StringRenderer* StringRenderer::getInstance()
{
	return instance;
}

void StringRenderer::drawCell(int col, int row, int srcX, int srcY, unsigned color) const
{
	GameLib::Framework f = GameLib::Framework::instance();
	unsigned* vram = f.videoMemory();
	int windowWidth = f.width();
	unsigned srcR = color & 0xff0000;
	unsigned srcG = color & 0x00ff00;
	unsigned srcB = color & 0x0000ff;
	for (int pixRow = 0; pixRow < fontHeight; pixRow++)
	{
		for (int pixCol = 0; pixCol < fontWidth; pixCol++)
		{
			int vramPixCol = col * fontWidth + pixCol;
			int vramPixRow = row * fontHeight + pixRow;
			if (vramPixCol >= windowWidth)
			{
				continue;
			}
			int srcPixCol = srcX + pixCol;
			int srcPixRow = srcY + pixRow;
			unsigned* dst = &vram[vramPixRow * windowWidth + vramPixCol];
			unsigned srcA = fontImage->getData()[srcPixRow * fontImage->getWidth() + srcPixCol] & 0xff;
			unsigned dstR = *dst & 0xff0000;
			unsigned dstG = *dst & 0x00ff00;
			unsigned dstB = *dst & 0x0000ff;
			unsigned r = (srcR - dstR) * srcA / 255 + dstR;
			unsigned g = (srcG - dstG) * srcA / 255 + dstG;
			unsigned b = (srcB - dstB) * srcA / 255 + dstB;
			*dst = (r & 0xff0000) | (g & 0x00ff00) | (b & 0x0000ff);
		}
	}
}

void StringRenderer::draw(int col, int row, const char* string, unsigned color) const
{
	int i = 0;
	char c = string[i];
	while (c != '\0')
	{
		if (c < 32 || c > 128)
		{
			c = 127;
		}
		else
		{
			c -= 32;
		}
		int srcCol = c % 16;
		int srcRow = c / 16;
		drawCell(col + i, row, srcCol * fontWidth, srcRow * fontHeight, color);
		i++;
		c = string[i];
	}
}
