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
	//Usage of ios::binary to stream the file in bytes
	std::ifstream ifs(filename, std::ios::binary);

	//declaration of variables to store file properties
	char * HEADER_bmp_id = new char[2];
	unsigned int HEADER_bmp_size;
	char * HEADER_unused = new char[4];
	unsigned int HEADER_bmp_offset;
	unsigned int DIB_bytes;
	
/*
====================================================================
	reading individual bytes to assigning them to the variables
====================================================================
*/
	//BMP header
	ifs.read(HEADER_bmp_id, 2);
	ifs.read((char*)&HEADER_bmp_size, 4);
	ifs.read(HEADER_unused, 4);
	ifs.read((char*)&HEADER_bmp_offset, 4);

	//DIB Header
	ifs.read((char*)&DIB_bytes, 4);
/*
==================================
	displays file information
==================================
*/
	//BMP header
	std::cout << "|| BMP Header ||" << std::endl;
	std::string id(HEADER_bmp_id, 2);
	std::cout << "ID: ";
	std::cout << id << std::endl;
	std::cout << "Size: ";
	std::cout << HEADER_bmp_size;
	std::cout << " bytes" << std::endl;
	std::cout << "Offset: ";
	std::cout << HEADER_bmp_offset << std::endl;
	std::cout << std::endl;

	//DIB header
	std::cout << "|| DIB Header ||" << std::endl;
	std::cout << "Bytes: ";
	std::cout << DIB_bytes << std::endl;

/*
============================================
	stores the file into a class(object)
============================================
*/
	//BMP header
	m_image->setID(id);
	m_image->setSizeOfBitmap(HEADER_bmp_size);
	m_image->setOffset(HEADER_bmp_offset);
}
