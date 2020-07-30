#ifndef INCLUDED_FILE_H
#define INCLUDED_FILE_H

class File
{
private:
	int size;
	char* data;

public:
	File(const char* fileName);
	~File();
	int getSize() const;
	const char* getData() const;
	unsigned getUnsigned(int pos) const;
};

#endif // !INCLUDED_FILE_H
