#pragma once

#include <string>
#include "BitmapImage.h"

// #$pla$h Gang
class BitmapParser
{
public:

	BitmapParser(const std::string& filename);

	~BitmapParser();

	void parseHeader(const std::string& filename);
	void parseDIB(const std::string& filename);
	void parsePixelArray(const std::string& filename);
	void create(const std::string& filename2);

private:
	
	BitmapImage* m_image;
};