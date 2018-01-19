#include "stdafx.h"
#include "BitmapParser.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <vector>>

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
	char * HEADER_unused = new char[7];
	unsigned int HEADER_bmp_offset;
	unsigned int DIB_bytes;
	unsigned int DIB_pWidth;
	unsigned int DIB_pHeight;
	unsigned short DIB_plane;
	unsigned short DIB_bits;
	unsigned int DIB_pac;
	unsigned int DIB_raw;
	unsigned int DIB_res_horizontal;
	unsigned int DIB_res_verticle;
	unsigned int DIB_colours;
	unsigned int DIB_important_colours;
	unsigned int PA_buffer_b;
	unsigned int PA_buffer_r;
	unsigned int PA_buffer_g;
	unsigned int PA_padding;
	std::vector<int> PA_b;
	std::vector<int> PA_r;
	std::vector<int> PA_g;
	
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
	ifs.read((char*)&DIB_pWidth, 4);
	ifs.read((char*)&DIB_pHeight, 4);
	ifs.read((char*)&DIB_plane, 2);
	ifs.read((char*)&DIB_bits, 2);
	ifs.read((char*)&DIB_pac, 4);
	ifs.read((char*)&DIB_raw, 4);
	ifs.read((char*)&DIB_res_horizontal, 4);
	ifs.read((char*)&DIB_res_verticle, 4);
	ifs.read((char*)&DIB_colours, 4);
	ifs.read((char*)&DIB_important_colours, 4);

	//Pixel Array
	int i;
	i = (HEADER_bmp_offset - 54);
	if (i > 0)
	{
		char * HEADER_unused_2 = new char[i];
		ifs.read(HEADER_unused_2, i);
	}




/*
==================================
	displays file information
==================================
*/
	//BMP header
	std::cout << "|| BMP Header ||" << std::endl;
	std::string id(HEADER_bmp_id, 2);
	std::cout << "ID: " << id << std::endl;
	std::cout << "Size: " << HEADER_bmp_size << " bytes" << std::endl;
	std::cout << "Offset: " << HEADER_bmp_offset << std::endl;
	std::cout << std::endl;

	//DIB header
	std::cout << "|| DIB Header ||" << std::endl;
	std::cout << "Bytes: " << DIB_bytes << std::endl;
	std::cout << "Width: " << DIB_pWidth << std::endl;
	std::cout << "Height: " << DIB_pHeight << std::endl;
	std::cout << "No. of colour plane/s: " << DIB_plane << std::endl;
	std::cout << "Bits per pixel: " << DIB_bits << std::endl;
	std::cout << "Pixel array compression: " << DIB_pac << std::endl;
	std::cout << "Raw bitmap data: " << DIB_raw << " bytes" << std::endl;
	std::cout << "Horizontal  print resolution: " << DIB_res_horizontal << " pixels" << std::endl;
	std::cout << "Verticle print resolution: " << DIB_res_verticle << " pixels" << std::endl;
	std::cout << "Colours in the palette: " << DIB_colours << std::endl;
	std::cout << "Important colours (0 means all): " << DIB_important_colours << std::endl;

	PA_buffer_b = 0;
	PA_buffer_g = 0;
	PA_buffer_r = 0;

	//Pixel array
	std::cout << std::endl;
	std::cout << "|| Pixel Array ||" << std::endl;
	int t = 0;
	if (DIB_pWidth % 4 == 0)
	{
		while (!ifs.eof())
		{
			ifs.read((char*)&PA_buffer_b, 1);
			ifs.read((char*)&PA_buffer_g, 1);
			ifs.read((char*)&PA_buffer_r, 1);
			if (ifs.eof()) break;
			PA_b.push_back(PA_buffer_b);
			PA_g.push_back(PA_buffer_g);
			PA_r.push_back(PA_buffer_r);
			std::cout << PA_buffer_b << ", " << PA_buffer_g << ", " << PA_buffer_r << std::endl;
			PA_buffer_b = 0;
			PA_buffer_g = 0;
			PA_buffer_r = 0;
		}
	}
	else if (DIB_pWidth % 4 == 3)
	{
		while (!ifs.eof())
		{
			t++;
			if (t == DIB_pWidth)
			{
				ifs.read((char*)&PA_padding, 1);
				PA_padding = 0;
				t = 1;
			}
			ifs.read((char*)&PA_buffer_b, 1);
			ifs.read((char*)&PA_buffer_g, 1);
			ifs.read((char*)&PA_buffer_r, 1);
			if (ifs.eof()) break;
			PA_b.push_back(PA_buffer_b);
			PA_g.push_back(PA_buffer_g);
			PA_r.push_back(PA_buffer_r);
			std::cout << PA_buffer_b << ", " << PA_buffer_g << ", " << PA_buffer_r << std::endl;
			PA_buffer_b = 0;
			PA_buffer_g = 0;
			PA_buffer_r = 0;
		}
	}
	else if (DIB_pWidth % 4 == 2)
	{
		while (!ifs.eof())
		{
			t++;
			if (t == DIB_pWidth)
			{
				ifs.read((char*)&PA_padding, 1);
				PA_padding = 0;
				ifs.read((char*)&PA_padding, 1);
				PA_padding = 0;
				t = 1;
			}
			ifs.read((char*)&PA_buffer_b, 1);
			ifs.read((char*)&PA_buffer_g, 1);
			ifs.read((char*)&PA_buffer_r, 1);
			if (ifs.eof()) break;
			PA_b.push_back(PA_buffer_b);
			PA_g.push_back(PA_buffer_g);
			PA_r.push_back(PA_buffer_r);
			std::cout << PA_buffer_b << ", " << PA_buffer_g << ", " << PA_buffer_r << std::endl;
			PA_buffer_b = 0;
			PA_buffer_g = 0;
			PA_buffer_r = 0;
		}
	}
	else if (DIB_pWidth % 4 == 1)
	{
		while (!ifs.eof())
		{
			t++;
			if (t == DIB_pWidth)
			{
				ifs.read((char*)&PA_padding, 1);
				PA_padding = 0;
				ifs.read((char*)&PA_padding, 1);
				PA_padding = 0;
				ifs.read((char*)&PA_padding, 1);
				PA_padding = 0;
				t = 1;
			}
			ifs.read((char*)&PA_buffer_b, 1);
			ifs.read((char*)&PA_buffer_g, 1);
			ifs.read((char*)&PA_buffer_r, 1);
			if (ifs.eof()) break;
			PA_b.push_back(PA_buffer_b);
			PA_g.push_back(PA_buffer_g);
			PA_r.push_back(PA_buffer_r);
			std::cout << PA_buffer_b << ", " << PA_buffer_g << ", " << PA_buffer_r << std::endl;
			PA_buffer_b = 0;
			PA_buffer_g = 0;
			PA_buffer_r = 0;
		}
	}
	
	

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
