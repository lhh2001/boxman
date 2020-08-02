#include <fstream>
#include "File.h"

File::File(const char* fileName) : size(0), data(nullptr)
{
	std::ifstream in(fileName, std::ifstream::binary);
	if (in)
	{
		in.seekg(0, std::ifstream::end);
		size = static_cast<int>(in.tellg());
		in.seekg(0, std::ifstream::beg);
		data = new char[size];
		in.read(data, size);
	}
}

File::~File()
{
	delete[] data;
	data = nullptr;
}

int File::getSize() const
{
	return size;
}

const char* File::getData() const
{
	return data;
}

unsigned File::getUnsigned(int pos) const
{
	const unsigned char* up;
	up = reinterpret_cast<const unsigned char*>(data);
	up += pos;
	unsigned ret = 0;
	for (int i = 0; i <= 24; i += 8) //i表示移位数
	{
		ret |= (*up) << i;
		up++;
	}
	return ret;
}
