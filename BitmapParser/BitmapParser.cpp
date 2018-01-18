#include "stdafx.h"
#include "BitmapParser.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>

BitmapParser::BitmapParser(const std::string& filename)
{
	m_image = new BitmapImage();
	parse(filename);
}

BitmapParser::~BitmapParser()
{
	delete m_image;
}

void BitmapParser::parse(const std::string& filename)
{
	std::ifstream ifs(filename, std::ios::binary);
	char * HEADER_bmp_id = new char[2];
	unsigned int HEADER_bmp_size;
	char * HEADER_unused = new char[4];
	char * HEADER_bmp_offset = new char[4];
	

	ifs.read(HEADER_bmp_id, 2);

	ifs.read((char*)&HEADER_bmp_size, 4);

	std::string id(HEADER_bmp_id, 2);

	std::cout << id << std::endl;
	std::cout << HEADER_bmp_size << std::endl;

	
	//m_image->setSizeOfBitmap(HEADER_bmp_size);
	/*m_image->setID(id);
	std::cout << id << std::endl;
	std::cout << iHeader_size << std::endl;
	ifs.read(HEADER_unused, 4);
	ifs.read(HEADER_bmp_offset, 4);
	std::stringstream strOffset;
	strOffset << HEADER_bmp_offset;
	unsigned int intOffset;
	strOffset >> intOffset;
	m_image->setOffset(intOffset);

	
	std::cout << intOffset << std::endl;*/
	//std::cout << HEADER_bmp_offset << std::endl;
}
