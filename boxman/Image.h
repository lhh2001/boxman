#ifndef INCLUDED_IMAGE_H
#define INCLUDED_IMAGE_H

#include <map>

class Image
{
private:
	int width;
	int height;
	unsigned* data;

public:
	Image(const char* fileName);
	~Image();
	int getWidth() const;
	int getHeight() const;
	void draw(int x, int y, char object);
};

#endif // !INCLUDED_IMAGE_H
