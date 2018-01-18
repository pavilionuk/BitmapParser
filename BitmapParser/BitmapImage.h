#pragma once

#include <string>

class BitmapImage
{
public:

	BitmapImage();

	~BitmapImage();
	//BMP header
	void setID(const std::string& id);
	void setSizeOfBitmap(const int& sizeOfBitmap);
	void setOffset(const int& Offset);
	std::string getID();
	int getOffset();
	int getSizeOfBitmap();

	//DIB header
	void setBytes(const int& bytes);
	int getBytes();
	void setWidth(const int& width);
	void setHeight(const int& height);
	int getWidth();
	int getHeight();


private:
	//BMP header
	std::string m_ID;
	int m_sizeOfBitmap;
	int m_offset;

	//DIB header
	int m_bytes;
	int m_width;
	int m_height;
};

class BMPHeader
{

};

class DIBHeader
{

};