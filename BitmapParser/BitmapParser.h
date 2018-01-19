#pragma once

#include <string>
#include "BitmapImage.h"

class BitmapParser
{
public:

	BitmapParser(const std::string& filename);

	~BitmapParser();

	void parse(const std::string& filename);
	void create(const std::string& filename2);

private:
	
	BitmapImage* m_image;
};