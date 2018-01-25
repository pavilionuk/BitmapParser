#pragma once

#include <string>
#include <vector>

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
	void setWidth(const int& width);
	void setHeight(const int& height);
	void setPlane(const int& plane);
	void setBits(const int& bits);
	void setPac(const int& pac);
	void setRaw(const int& raw);
	void setResW(const int& resW);
	void setResH(const int& resH);
	void setColours(const int& colours);
	void setiColours(const int& icolours);
	void addBlanks(int& blanks);

	int getBytes();
	int getWidth();
	int getHeight();
	int getPlane();
	int getBits();
	int getPac();
	int getRaw();
	int getResW();
	int getResH();
	int getColours();
	int getiColours();
	std::vector<int> getBlanks();



	//Pixel array
	void addPixel8(int& pixel);

	void addPixel4(int& pixel);

	void add2b(int& pa_b);
	void add2g(int& pa_g);
	void add2r(int& pa_r);
	void addAlpha(int& alpha);
	void setPadding(const int& padding);

	std::vector<int> getAlpha();

	std::vector<int> getPixel8();

	std::vector<int> getPixel4();

	std::vector<int> getB();
	std::vector<int> getG();
	std::vector<int> getR();
	int getPadding();

private:
	//BMP header
	std::string m_ID;
	int m_sizeOfBitmap;
	int m_offset;

	//DIB header
	int m_bytes;
	int m_width;
	int m_height;
	int m_planes;
	int m_bits;
	int m_pac;
	int m_raw;
	int m_resW;
	int m_resH;
	int m_colours;
	int m_icolours;
	std::vector<int> m_blanks;
	
	//Pixel array
	std::vector<int> m_pixel8;

	std::vector<int> m_pixel4;

	std::vector<int> m_PA_b;
	std::vector<int> m_PA_g;
	std::vector<int> m_PA_r;
	std::vector<int> m_alpha;
	int m_padding;
};