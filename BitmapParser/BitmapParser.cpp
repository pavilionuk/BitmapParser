#include "stdafx.h"
#include "BitmapParser.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>

BitmapParser::BitmapParser(const std::string& filename)
{
	m_image = new BitmapImage();
	parseHeader(filename);
	parseDIB(filename);
	parsePixelArray(filename);
	const std::string filename2 = R"(C:\Users\pavilion.sahota\Desktop\output\output.bmp)";
	create(filename2);
}

BitmapParser::~BitmapParser()
{
	delete m_image;
}

std::vector<unsigned char> arrayOfByte(int paramInt, int allocation)
{
	std::vector<unsigned char> arrayOfByte(allocation);
	for (int i = 0;i < allocation;i++)
	{
		arrayOfByte[3 - i] = (paramInt >> (i * 8));
	}
	return arrayOfByte;
}

void justForFun()
{
	while (true) { std::cout << "Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  " << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << "emes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  M" << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << "mes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Me" << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << "es  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Mem" << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << "s  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Meme" << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << "  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes" << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << " Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes " << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
}

void BitmapParser::create(const std::string& filename2)
{
	std::cout << "|| File re-creation ||" << std::endl;

	std::ofstream ofs(filename2, std::ios::binary);


	std::string id = m_image->getID();
	char* id_bytes = _strdup(id.c_str());

	ofs.write(id_bytes, 2);

	//unsigned int microseconds = 100000;
	unsigned char* size = (unsigned char*)m_image->getSizeOfBitmap();
	unsigned char* unused = (unsigned char*)0;
	unsigned char* offset = (unsigned char*)m_image->getOffset();
	unsigned char* bytes = (unsigned char*)m_image->getBytes();
	unsigned char* width = (unsigned char*)m_image->getWidth();
	unsigned char* height = (unsigned char*)m_image->getHeight();
	unsigned char* plane = (unsigned char*)m_image->getPlane();
	unsigned char* bits = (unsigned char*)m_image->getBits();
	unsigned char* pac = (unsigned char*)m_image->getPac();
	unsigned char* raw = (unsigned char*)m_image->getRaw();
	unsigned char* resW = (unsigned char*)m_image->getResW();
	unsigned char* resH = (unsigned char*)m_image->getResH();
	unsigned char* colours = (unsigned char*)m_image->getColours();
	unsigned char* icolours = (unsigned char*)m_image->getiColours();
	int iBits = m_image->getBits();

	ofs.write((char*)&size, 4);
	ofs.write((char*)&unused, 4);
	ofs.write((char*)&offset, 4);

	ofs.write((char*)&bytes, 4);
	ofs.write((char*)&width, 4);
	ofs.write((char*)&height, 4);
	ofs.write((char*)&plane, 2);
	ofs.write((char*)&bits, 2);
	ofs.write((char*)&pac, 4);
	ofs.write((char*)&raw, 4);
	ofs.write((char*)&resW, 4);
	ofs.write((char*)&resH, 4);
	ofs.write((char*)&colours, 4);
	ofs.write((char*)&icolours, 4);

	const int padding = 0;

	unsigned char* pad = (unsigned char*)padding;

	if (m_image->getOffset()>54)
	{
		std::vector<int> blanks = m_image->getBlanks();
		for (int i = 0; i < m_image->getOffset();i++)
		{
			ofs.write((char*)&blanks.at(i), 1);
		}
	}

	//std::cout << "Pixels to process: " << b.size() << std::endl;
	switch (iBits)
	{
	case 32:
	{
		std::vector<int> b = m_image->getB();
		std::vector<int> g = m_image->getG();
		std::vector<int> r = m_image->getR();
		std::vector<int> a = m_image->getAlpha();

		for (size_t i = 0; i < b.size(); i++)
		{
			//This makes it look prettier but slows down the processing
			//std::cout << "Completed pixel: " << i << "/" << b.size() << '\r';

			unsigned char* blue = (unsigned char*)b.at(i);
			unsigned char* green = (unsigned char*)g.at(i);
			unsigned char* red = (unsigned char*)r.at(i);
			unsigned char* alpha = (unsigned char*)a.at(i);

			ofs.write((char*)&blue, 1);
			ofs.write((char*)&green, 1);
			ofs.write((char*)&red, 1);
			ofs.write((char*)&alpha, 1);
		}
		ofs.close();
		std::cout << "File re-creation completed!" << std::endl;
		std::cout << std::endl;
		break;
	}
	case 24:
	{
		int t = 1;
		std::vector<int> b = m_image->getB();
		std::vector<int> g = m_image->getG();
		std::vector<int> r = m_image->getR();

		for (size_t i = 0; i < b.size(); i++)
		{
			//This makes it look prettier but slows down the processing
			//std::cout << "Completed pixel: " << i << "/" << b.size() << '\r';

			unsigned char* blue = (unsigned char*)b.at(i);
			unsigned char* green = (unsigned char*)g.at(i);
			unsigned char* red = (unsigned char*)r.at(i);

			ofs.write((char*)&blue, 1);
			ofs.write((char*)&green, 1);
			ofs.write((char*)&red, 1);

			if (t == m_image->getWidth())
			{
				if (m_image->getPadding() == 1)
				{
					ofs.write((char*)&pad, 1);
				}
				else if (m_image->getPadding() == 2)
				{
					ofs.write((char*)&pad, 1);
					ofs.write((char*)&pad, 1);
				}
				else if (m_image->getPadding() == 3)
				{
					ofs.write((char*)&pad, 1);
					ofs.write((char*)&pad, 1);
					ofs.write((char*)&pad, 1);
				}
				t = 0;
			}
			t++;
		}
		ofs.close();
		std::cout << "File re-creation completed!" << std::endl;
		std::cout << std::endl;
		break;
	}

	case 16:
	{
		std::cout << "BitmapParser is currently unable to process bmp files with a 16bit colour depth" << std::endl;
		break;
	}

	case 8:
	{
		int t = 1;
		std::vector<int> pixel8 = m_image->getPixel8();
		for (size_t i = 0; i < pixel8.size(); i++)
		{
			//This makes it look prettier but slows down the processing
			//std::cout << "Completed pixel: " << i << "/" << b.size() << '\r';

			std::vector<int> pixel8 = m_image->getPixel8();
			unsigned char* pixel8char = (unsigned char*)pixel8.at(i);

			ofs.write((char*)&pixel8char, 1);

			if (t == m_image->getWidth())
			{
				if (m_image->getPadding() == 1)
				{
					ofs.write((char*)&pad, 1);
				}
				else if (m_image->getPadding() == 2)
				{
					ofs.write((char*)&pad, 1);
					ofs.write((char*)&pad, 1);
				}
				else if (m_image->getPadding() == 3)
				{
					ofs.write((char*)&pad, 1);
					ofs.write((char*)&pad, 1);
					ofs.write((char*)&pad, 1);
				}
				t = 0;
			}
			t++;
		}
		ofs.close();
		std::cout << "File re-creation completed!" << std::endl;
		std::cout << std::endl;
		break;
	}

	case 4:
	{
		int padRemainder = ((m_image->getWidth() / 2) % 4);
		int padding = (4 - padRemainder);
		if (padding == 4) padding = 0;

		int t = 1;
		std::vector<int> pixel4 = m_image->getPixel4();
		for (size_t i = 0; i < pixel4.size();)
		{
			int pixel4char1 = pixel4.at(i++);

			if (i == pixel4.size()) break;

			int pixel4char2 = pixel4.at(i++);

			int buffer = 0;
			buffer = buffer | pixel4char1;
			buffer = buffer << 4;

			buffer = buffer | pixel4char2;

			ofs.put(buffer);
			if (t == m_image->getWidth())
			{
				if (padding == 1)
				{
					ofs.write((char*)&pad, 1);
				}
				else if (padding == 2)
				{
					ofs.write((char*)&pad, 1);
					ofs.write((char*)&pad, 1);
				}
				else if (padding == 3)
				{
					ofs.write((char*)&pad, 1);
					ofs.write((char*)&pad, 1);
					ofs.write((char*)&pad, 1);
				}
				t = 0;
			}
			t++;
		}
		break;
	}

	default:
	{
		break;
	}
	}
	ofs.close();
	justForFun();
}

/*
 || /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ||
 || ++++++++++++++++ - Parses the main header - ++++++++++++++++ ||
 || \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ ||
*/
void BitmapParser::parseHeader(const std::string& filename)
{
	//binary file stream
	std::ifstream ifs(filename, std::ios::binary);

	//define variables
	char * header_id = new char[2];
	unsigned int header_size;
	char * header_unused = new char[4];
	unsigned int header_offset;

	//reads the data into those variables
	ifs.read(header_id, 2);
	ifs.read((char*)&header_size, 4);
	ifs.read(header_unused, 4);
	ifs.read((char*)&header_offset, 4);

	//data display
	std::cout << "|| BMP Header ||" << std::endl;
	std::string id(header_id, 2);
	std::cout << "ID: " << id << std::endl;
	std::cout << "Size: " << header_size << "B";
	if (header_size / 1000 > 0) std::cout << " || " << header_size / 1000 << "KB";
	if (header_size / 1000000 > 0) std::cout << " || " << header_size / 1000000 << "MB";
	if (header_size / 1000000000 > 0) std::cout << " || " << header_size / 1000000000 << "GB";
	std::cout << std::endl;
	std::cout << "Offset: " << header_offset << std::endl;
	std::cout << std::endl;

	//stores the variables in the class "m_image"
	m_image->setID(id);
	m_image->setSizeOfBitmap(header_size);
	m_image->setOffset(header_offset);
}

/*
 || /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ||
 || ++++++++++++++++ - Parses the DIB header - +++++++++++++++++ ||
 || \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ ||
*/
void BitmapParser::parseDIB(const std::string& filename)
{
	//binary file stream
	std::ifstream ifs(filename, std::ios::binary);

	//define variables
	char * skip_header = new char[14];
	unsigned int dib_bytes;
	unsigned int dib_pWidth;
	unsigned int dib_pHeight;
	unsigned short dib_plane;
	unsigned short dib_bits_per_pixel;
	unsigned int dib_bi_pixel_array_compression;
	unsigned int dib_raw;
	unsigned int dib_horizontal_resolution;
	unsigned int dib_verticle_resolution;
	unsigned int dib_colours;
	unsigned int dib_important_colours;

	//skips the reading straight to the offset
	ifs.read(skip_header, 14);
	delete skip_header;

	//reads the data into those variables
	ifs.read((char*)&dib_bytes, 4);
	ifs.read((char*)&dib_pWidth, 4);
	ifs.read((char*)&dib_pHeight, 4);
	ifs.read((char*)&dib_plane, 2);
	ifs.read((char*)&dib_bits_per_pixel, 2);
	ifs.read((char*)&dib_bi_pixel_array_compression, 4);
	ifs.read((char*)&dib_raw, 4);
	ifs.read((char*)&dib_horizontal_resolution, 4);
	ifs.read((char*)&dib_verticle_resolution, 4);
	ifs.read((char*)&dib_colours, 4);
	ifs.read((char*)&dib_important_colours, 4);

	//any extra data stored in the DIB will be stored for recreation later on
	if (m_image->getOffset() > 54)
	{
		int buffer;
		int offset = m_image->getOffset();
		for (int i = 0; i < offset; i++)
		{
			ifs.read((char*)&buffer, 1);
			m_image->addBlanks(buffer);
			buffer = 0;
		}
	}

	//data display
	std::cout << "|| DIB Header ||" << std::endl;
	std::cout << "Bytes: " << dib_bytes << std::endl;
	std::cout << "Width: " << dib_pWidth << std::endl;
	std::cout << "Height: " << dib_pHeight << std::endl;
	std::cout << "No. of colour plane/s: " << dib_plane << std::endl;
	std::cout << "Bits per pixel: " << dib_bits_per_pixel << std::endl;
	std::cout << "Pixel array compression: " << dib_bi_pixel_array_compression << std::endl;
	std::cout << "Raw bitmap data: " << dib_raw << " bytes" << std::endl;
	std::cout << "Horizontal  print resolution: " << dib_horizontal_resolution << " pixels" << std::endl;
	std::cout << "Verticle print resolution: " << dib_verticle_resolution << " pixels" << std::endl;
	std::cout << "Colours in the palette: " << dib_colours << std::endl;
	std::cout << "Important colours (0 means all): " << dib_important_colours << std::endl;
	std::cout << std::endl;

	//stores the variables in the class "m_image"
	m_image->setBytes(dib_bytes);
	m_image->setWidth(dib_pWidth);
	m_image->setHeight(dib_pHeight);
	m_image->setPlane(dib_plane);
	m_image->setBits(dib_bits_per_pixel);
	m_image->setPac(dib_bi_pixel_array_compression);
	m_image->setRaw(dib_raw);
	m_image->setResH(dib_horizontal_resolution);
	m_image->setResW(dib_verticle_resolution);
	m_image->setColours(dib_colours);
	m_image->setiColours(dib_important_colours);
}

/*
 || /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ||
 || ++++++++++++++++ - Parses the pixel array for each colour depth - ++++++++++++++++ ||
 || \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ ||
*/
void BitmapParser::parsePixelArray(const std::string& filename)
{
	//binary file stream
	std::ifstream ifs(filename, std::ios::binary);

	//skips the reading straight to the offset
	int skip = m_image->getOffset();
	char * skip_header = new char[skip];
	ifs.read(skip_header, skip);
	delete skip_header, skip;

	//defining variables to identify what kind of bmp file needs to be processed
	int pad = 0;
	int t = 0;
	int bit = m_image->getBits();

	//data display
	std::cout << "|| Pixel Array ||" << std::endl;
	std::cout << "Processing..." << std::endl;

	//processes the pixel array according to the structure defined by the colour depth
	switch (bit)
	{

	//32 bits per pixel, each pixel takes up 4 bytes and has 4,294,967,296 distinct colours
	case 32:
	{
		int blueBuffer;
		int greenBuffer;
		int redBuffer;
		int alphaBuffer;

		while (!ifs.eof())
		{
			ifs.read((char*)&blueBuffer, 1);
			ifs.read((char*)&greenBuffer, 1);
			ifs.read((char*)&redBuffer, 1);
			ifs.read((char*)&alphaBuffer, 1);
			if (ifs.eof()) break;
			m_image->add2b(blueBuffer);
			m_image->add2g(greenBuffer);
			m_image->add2r(redBuffer);
			m_image->addAlpha(alphaBuffer);
			blueBuffer = 0;
			greenBuffer = 0;
			redBuffer = 0;
			alphaBuffer = 0;
		}
		std::cout << "Processing completed!" << std::endl;
		std::cout << std::endl;
		m_image->setPadding(0);
		break;
	}

	//24 bits per pixel, each pixel takes up 3 bytes and has 16,777,216 distinct colours
	case 24:
	{
		int padRemainder = ((m_image->getWidth() * 3) % 4);
		int padding = 4 - padRemainder;
		if (padRemainder == 0) padding = 0;
		int blueBuffer;
		int greenBuffer;
		int redBuffer;

		while (!ifs.eof())
		{
			if (padding > 0)
			{
				if (t == m_image->getWidth())
				{
					for (int i = 0; i < padding;i++)
					{
						ifs.read((char*)&pad, 1);
						pad = 0;
					}
					t = 0;
				}
			}
			ifs.read((char*)&blueBuffer, 1);
			ifs.read((char*)&greenBuffer, 1);
			ifs.read((char*)&redBuffer, 1);
			if (ifs.eof()) break;
			m_image->add2b(blueBuffer);
			m_image->add2g(greenBuffer);
			m_image->add2r(redBuffer);
			blueBuffer = 0;
			greenBuffer = 0;
			redBuffer = 0;
			t++;
		}
		std::cout << "Processing completed!" << std::endl;
		std::cout << std::endl;
		m_image->setPadding(padding);
		break;
	}

	//16 bits per pixel, each pixel takes up 2 bytes and has 65,536 distinct colours
	case 16:
	{
		int firstIndex;
		int secondIndex;
		int pixelBuffer;

		while (!ifs.eof())
		{
			ifs.read((char*)&pixelBuffer, 1);
			if (ifs.eof()) break;
			firstIndex = pixelBuffer & 0xF0;
			firstIndex = firstIndex >> 4;
			secondIndex = pixelBuffer & 0x0F;
			secondIndex = secondIndex >> 0;
			m_image->add2b(firstIndex);
			m_image->add2g(secondIndex);
			pixelBuffer = 0;
			
			ifs.read((char*)&pixelBuffer, 1);
			firstIndex = pixelBuffer & 0xF0;
			firstIndex = firstIndex >> 4;
			secondIndex = pixelBuffer & 0x0F;
			secondIndex = secondIndex >> 0;
			m_image->add2r(firstIndex);
			m_image->addAlpha(secondIndex);
			pixelBuffer = 0;
		}
		std::cout << "Processing completed!" << std::endl;
		std::cout << std::endl;
		m_image->setPadding(0);
		break;
	}

	//8 bits per pixel, each pixel takes up 1 byte and has 256 distinct colours
	case 8:
	{
		int padRemainder = (m_image->getWidth() % 4);
		int padding = (4 - padRemainder);
		if (padding == 4) padding = 0;
		int pixelBuffer;

		while (!ifs.eof())
		{
			if (padding > 0)
			{
				if (t == m_image->getWidth())
				{
					for (int i = 0; i < padding;i++)
					{
						ifs.read((char*)&pad, 1);
						pad = 0;
					}
					t = 0;
				}
			}
			ifs.read((char*)&pixelBuffer, 1);
			if (ifs.eof()) break;
			m_image->addPixel8(pixelBuffer);
			pixelBuffer = 0;
			t++;
		}
		std::cout << "Processing completed!" << std::endl;
		std::cout << std::endl;
		m_image->setPadding(padding);
		break;
	}

	//4 bits per pixel, 1 byte stores 2 pixels in this case, 16 distinct colours
	case 4:
	{
		int padRemainder = ((m_image->getWidth() /2) % 4);
		int padding = (4 - padRemainder);
		if (padding == 4) padding = 0;

		int pixelBuffer;
		int firstIndex;
		int secondIndex;
		
		while (!ifs.eof())
		{
			if (padding > 0)
			{
				if (t == m_image->getWidth())
				{
					for (int i = 0; i < padding;i++)
					{
						ifs.read((char*)&pad, 1);
						pad = 0;
					}
					t = 0;
				}
			}
			ifs.read((char*)&pixelBuffer, 1);
			if (ifs.eof()) break;
			firstIndex = pixelBuffer & 0xF0;
			firstIndex = firstIndex >> 4;
			secondIndex = pixelBuffer & 0x0F;
			secondIndex = secondIndex >> 0;
			m_image->addPixel4(firstIndex);
			m_image->addPixel4(secondIndex);
			t++;
		}
		std::cout << "Processing completed!" << std::endl;
		std::cout << std::endl;
		m_image->setPadding(padding);
		break;
	}

	default:
		std::cout << "BitmapParser is unable to determine the file's properties, please try another file." << std::endl;
		break;
	}
}
