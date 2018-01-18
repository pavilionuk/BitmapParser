#pragma once

#include <string>

class BitmapImage
{
public:

	BitmapImage();

	~BitmapImage();

	void setID(const std::string& id);
	void setSizeOfBitmap(const int& sizeOfBitmap);
	void setOffset(const int & Offset);
	std::string getID();
	int getSizeOfBitmap();

private:
	//header
	std::string m_ID;
	int m_sizeOfBitmap;
	int m_offset;
};

