#ifndef INCLUDED_STRING_RENDERER_H
#define INCLUDED_STRING_RENDERER_H

class Image;

class StringRenderer
{
public:
	static StringRenderer* getInstance();
	static void create(const char* fileName);
	static void destroy();
	void draw(int col, int row, const char* string, unsigned color = 0xffffff) const;
	//col和row是文字显示在屏幕上的行号和列号

private:
	StringRenderer();
	StringRenderer(const char* fileName);
	StringRenderer(const StringRenderer&);
	~StringRenderer();
	void drawCell(int col, int row, int srcX, int srcY, unsigned color) const;
	static StringRenderer* instance;
	Image* fontImage;
	const int fontHeight = 16;
	const int fontWidth = 8;
};

#endif // !INCLUDED_STRING_RENDERER_H
