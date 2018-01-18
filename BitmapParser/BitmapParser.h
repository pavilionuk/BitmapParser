#pragma once

#include <string>
#include "BitmapImage.h"

class BitmapParser
{
public:

	BitmapParser(const std::string& filename);

	~BitmapParser();

	void parse(const std::string& filename);

private:
	
	BitmapImage* m_image;
};