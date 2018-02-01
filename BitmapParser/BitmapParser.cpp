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
#include <algorithm>

// #$pla$h Gang
bool isFailed = false;
BitmapParser::BitmapParser(const std::string& filename)
{
	m_image = new BitmapImage();
	parseHeader(filename);
	if (isFailed == false)
	{
		parseDIB(filename);
		parsePixelArray(filename);
		const std::string filename2 = R"(C:\Users\pavilion.sahota\Desktop\output\output.bmp)";
		create(filename2);
	}
}

BitmapParser::~BitmapParser()
{
	delete m_image;
}


// NOTHING TO SEE HERE, PLEASE DISREGARD THIS FUNCTION AND MOVE ON
int progressCounter = 0;
void progressAnimation()
{
	progressCounter++;
	if (progressCounter == 500000) { std::cout << "Processing [=-------------------]" << '\r'; }
	else if (progressCounter == 1000000) { std::cout << "Processing [0=------------------]" << '\r'; }
	else if (progressCounter == 1500000) { std::cout << "Processing [80=-----------------]" << '\r'; }
	else if (progressCounter == 2000000) { std::cout << "Processing [880=----------------]" << '\r'; }
	else if (progressCounter == 2500000) { std::cout << "Processing [0880=---------------]" << '\r'; }
	else if (progressCounter == 3000000) { std::cout << "Processing [=0880=--------------]" << '\r'; }
	else if (progressCounter == 3500000) { std::cout << "Processing [-=0880=-------------]" << '\r'; }
	else if (progressCounter == 4000000) { std::cout << "Processing [--=0880=------------]" << '\r'; }
	else if (progressCounter == 4500000) { std::cout << "Processing [---=0880=-----------]" << '\r'; }
	else if (progressCounter == 4500000) { std::cout << "Processing [----=0880=----------]" << '\r'; }
	else if (progressCounter == 5000000) { std::cout << "Processing [-----=0880=---------]" << '\r'; }
	else if (progressCounter == 5500000) { std::cout << "Processing [------=0880=--------]" << '\r'; }
	else if (progressCounter == 6000000) { std::cout << "Processing [-------=0880=-------]" << '\r'; }
	else if (progressCounter == 6500000) { std::cout << "Processing [--------=0880=------]" << '\r'; }
	else if (progressCounter == 7000000) { std::cout << "Processing [---------=0880=-----]" << '\r'; }
	else if (progressCounter == 7500000) { std::cout << "Processing [----------=0880=----]" << '\r'; }
	else if (progressCounter == 8000000) { std::cout << "Processing [-----------=0880=---]" << '\r'; }
	else if (progressCounter == 8500000) { std::cout << "Processing [------------=0880=--]" << '\r'; }
	else if (progressCounter == 9000000) { std::cout << "Processing [-------------=0880=-]" << '\r'; }
	else if (progressCounter == 9500000) { std::cout << "Processing [--------------=0880=]" << '\r'; }
	else if (progressCounter == 10000000) { std::cout << "Processing [---------------=0880]" << '\r'; }
	else if (progressCounter == 10500000) { std::cout << "Processing [----------------=088]" << '\r'; }
	else if (progressCounter == 11000000) { std::cout << "Processing [-----------------=08]" << '\r'; }
	else if (progressCounter == 11500000) { std::cout << "Processing [------------------=0]" << '\r'; }
	else if (progressCounter == 12000000) { std::cout << "Processing [-------------------=]" << '\r'; }
	else if (progressCounter == 12500000) { std::cout << "Processing [--------------------]" << '\r';progressCounter = 0; }
}
/*
				 [::]===========================================================[::]
	 /M\         <|| /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//\/\/\/\/\ ||>         /M\
   <|[o]|00===00<<|| ++++++++++++++++ - Recreate the bmp file - ++++++++++++++++ ||>>00===00|[o]|>
	 \W/         <|| \/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ ||>         \W/
				 [::]===========================================================[::]
*/
int currentNum = 0;
int icon = 0;
void progressBar(int size, int current)
{
	float currentPercent = (100.0 / (float)size) * (float)current;
	if (currentNum != (int)currentPercent)
	{
		std::cout << "Progress: " << (int)currentPercent << "%   [";
		currentNum = currentPercent;
		if (icon == 0)
		{
			std::cout << "|]";
			icon = 1;
			std::cout << '\r';
		}
		else if (icon == 1)
		{
			std::cout << "/]";
			icon = 2;
			std::cout << '\r';
		}
		else if (icon == 2)
		{
			std::cout << "-]";
			icon = 3;
			std::cout << '\r';
		}
		else if (icon == 3)
		{
			std::cout << R"(\])";
			icon = 0;
			std::cout << '\r';
		}
	}
}
void BitmapParser::create(const std::string& filename2)
{
	std::cout << "|| File re-creation ||" << std::endl;

	std::ofstream ofs(filename2, std::ios::binary);

	std::string id = m_image->getID();
	char* id_bytes = _strdup(id.c_str());
	ofs.write(id_bytes, 2);

	int size = m_image->getSizeOfBitmap();
	int unused = 0;
	int offset = m_image->getOffset();
	int bytes = m_image->getBytes();
	int width = m_image->getWidth();
	int height = m_image->getHeight();
	int plane = m_image->getPlane();
	int bits = m_image->getBits();
	int pac = m_image->getPac();
	int raw = m_image->getRaw();
	int resW = m_image->getResW();
	int resH = m_image->getResH();
	int colours = m_image->getColours();
	int icolours = m_image->getiColours();
	int iBits = m_image->getBits();

	ofs.write((char*)&size, 4);
	ofs.write((char*)&unused, 4);
	ofs.write((char*)&offset, 4);

	ofs.write((char*)&bytes, 4);
	ofs.write((char*)&width, 4);
	ofs.write((char*)&height, 4);
	ofs.write((char*)&plane, 2);

	bool RLE4 = false;
	bool RLE8 = false;
	int pac2;

	std::string yesno;
	if (int(bits) == 4)
	{
		std::cout << "Would you like to incorporate RLE4 compression Y/N? : ";
		std::cin >> yesno;
		if (yesno == "Y" || yesno == "y" || yesno == "yes" || yesno == "Yes" || yesno == "YES")
		{
			RLE4 = true;
			pac2 = 2;
		}
		else
		{
			RLE4 = false;
		}
	}
	else if (int(bits) == 8)
	{
		std::cout << "Would you like to incorporate RLE8 compression Y/N? : ";
		std::cin >> yesno;
		if (yesno == "Y" || yesno == "y" || yesno == "yes" || yesno == "Yes" || yesno == "YES")
		{
			RLE8 = true;
			pac2 = 1;
		}
		else
		{
			RLE8 = false;
		}
	}

	ofs.write((char*)&bits, 2);
	if (RLE4 == true)
	{
		ofs.write((char*)&pac2, 4);
	}
	else if (RLE8 == true)
	{
		ofs.write((char*)&pac2, 4);
	}
	else
	{
		ofs.write((char*)&pac, 4);
	}
	ofs.write((char*)&raw, 4);
	ofs.write((char*)&resW, 4);
	ofs.write((char*)&resH, 4);
	ofs.write((char*)&colours, 4);
	ofs.write((char*)&icolours, 4);

	const int padding = 0;
	int pad = padding;
	int offset2 = m_image->getOffset();
	if (offset2 > 54)
	{
		offset2 -= 54;
		std::vector<int> blanks = m_image->getBlanks();
		for (int i = 0; i < offset2;i++)
		{
			ofs.write((char*)&blanks.at(i), 1);
		}
	}
	std::cout << "Progress: 0%" << '\r';
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
			progressBar((b.size() + 1), i);

			int blue = b.at(i);
			int green = g.at(i);
			int red = r.at(i);
			int alpha = a.at(i);

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
			progressBar((b.size() + 1), i);

			int blue = b.at(i);
			int green = g.at(i);
			int red = r.at(i);

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
		//TODO: finish this section of code
		std::cout << "BitmapParser is currently unable to process bmp files with a 16bit colour depth" << std::endl;
		break;
	}

	case 8:
	{
		int t = 1;
		std::vector<int> pixel8 = m_image->getPixel8();

		if (RLE8 == true)
		{
			int counter = 1;
			int counter2 = 1;
			int buffer = 0;
			std::vector<int> pixel8 = m_image->getPixel8();
			for (size_t i = 0; i < pixel8.size(); i++)
			{
				//std::cout << "Iterator: " << i << "/" << pixel8.size() << "     " << '\r';
				if (i >= pixel8.size()) break;
				if (i >= pixel8.size()-1) break;
				if (pixel8.at(i) == pixel8.at(i + counter))
				{
					while (pixel8.at(i) == pixel8.at(i + counter))
					{
						counter++;
					}

					ofs.write((char*)&counter, 1);
					buffer = pixel8.at(i);
					ofs.write((char*)&buffer, 1);
					i += counter;
					counter = 1;
					if (i >= pixel8.size()) break;
				}
				else
				{
					if (pixel8.at(i + counter2) != pixel8.at(i + (counter2 + 1)))
					{
						while (pixel8.at(i + counter2) != pixel8.at(i + (counter2 + 1)))
						{
							counter2++;
						}
						buffer = 0;
						ofs.write((char*)&buffer, 1);
						ofs.write((char*)&counter2, 1);
						for (int b = 0; b < counter2; b++)
						{
							ofs.write((char*)&pixel8.at(i + b), 1);
						}
						i += counter2;
					}
					counter2 = 1;
					if (i == pixel8.size()) break;
				}
				if (i >= pixel8.size()) break;
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
			}
		}
		else if (RLE8 == false)
		{
			std::vector<int> pixel8 = m_image->getPixel8();
			for (size_t i = 0; i < pixel8.size(); i++)
			{
				progressBar((pixel8.size() + 1), i);
				int pixel8char = pixel8.at(i);
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
		}
		ofs.close();
		std::cout << "File re-creation completed!" << std::endl;
		std::cout << std::endl;
		break;
	}
	case 4:
	{
		/*
		//identifying the amount of padding required (if any).
		int padRemainder = ((m_image->getWidth() / 2) % 4);
		int padding = (4 - padRemainder);
		if (padding == 4) padding = 0;

		//counter
		int t = 1;
		//retrieving the vector of pixels
		std::vector<int> pixel4 = m_image->getPixel4();
		//loop until there are no more pixels to write
		for (size_t i = 0; i < pixel4.size();)
		{
			//takes a 4-bit pixel out of the vector
			int pixel4char1 = pixel4.at(i++);
			//break out of loop if there are no more pixels to write
			if (i == pixel4.size()) break;
			//takes another 4-bit pixel out of the vector
			int pixel4char2 = pixel4.at(i++);
			//define a buffer
			int buffer = 0;
			//use the buffer to merge the 2 4-bit pixels into a 2 pixel byte
			buffer = buffer | pixel4char1;
			buffer = buffer << 4;

			buffer = buffer | pixel4char2;
			//write the 2 pixel byte to the file
			ofs.put(buffer);
			//if it has reached the end of the row
			if (t == m_image->getWidth())
			{
				//if padding is required
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
			*/
		if (RLE4 == true)
		{
			int counter = 1;
			int counter2 = 1;
			int buffer = 0;
			std::vector<int> pixel4 = m_image->getPixel4();
			for (size_t i = 0; i < pixel4.size(); i++)
			{
				progressBar((pixel4.size() + 1), i);
				if (pixel4.at(i) == pixel4.at(i + counter))
				{
					while (pixel4.at(i) == pixel4.at(i + counter))
					{
						counter++;
					}

					ofs.write((char*)&counter, 1);
					buffer = pixel4.at(i);
					ofs.write((char*)&buffer, 1);
					i += counter;
					counter = 1;
				}
				else
				{
					if (pixel4.at(i + counter2) != pixel4.at(i + (counter2 + 1)))
					{
						while (pixel4.at(i + counter2) != pixel4.at(i + (counter2 + 1)))
						{
							counter2++;
						}
						buffer = 0;
						ofs.write((char*)&buffer, 1);
						ofs.write((char*)&counter2, 1);
						for (int b = 0; b < counter2; b++)
						{
							ofs.write((char*)&pixel4.at(i + b), 1);
						}
						i += counter2;
					}
					counter2 = 1;
					if (i == pixel4.size()) break;
				}
			}
		}
		else
		{
			std::vector<int> pixel4 = m_image->getPixel4();
			for (size_t i = 0; i < pixel4.size(); i++)
			{
				progressBar((pixel4.size() + 1), i);
				int buffer = pixel4.at(i);
				if (i == pixel4.size()) break;
				ofs.write((char*)&buffer, 1);
			}
		}
		/*
		std::vector<int> pixel4 = m_image->getPixel4();
		for (size_t i = 0; i < pixel4.size(); i++)
		{
			int buffer = pixel4.at(i);
			if (i == pixel4.size()) break;
			ofs.write((char*)&buffer, 1);
		}
		*/
		break;
	}
	default:
	{
		break;
	}
	ofs.close();
	std::cout << "Parsing Complete!     " << std::endl;
	std::cout << std::endl;
	}
}

/*
				 [::]============================================================[::]
	 /M\         <|| /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ||>         /M\
   <|[o]|00===00<<|| ++++++++++++++++ - Parses the main header - ++++++++++++++++ ||>>00===00|[o]|>
	 \W/         <|| \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ ||>         \W/
				 [::]============================================================[::]
*/
void BitmapParser::parseHeader(const std::string& filename)
{
	std::ifstream ifs(filename, std::ios::binary);

	char * header_id = new char[2];
	unsigned int header_size;
	char * header_unused = new char[4];
	unsigned int header_offset;

	ifs.read(header_id, 2);
	std::string str(header_id, 2);
	if (header_id == NULL || str != "BM")
	{
		isFailed = true;
		std::cout << "!! BitmapParser is unable to open the target file !!" << std::endl;
		std::cout << std::endl;
		std::cout << "This could be due to the following reasons:" << std::endl;
		std::cout << "- The target file does not exist" << std::endl;
		std::cout << "- The target file is not a bitmap" << std::endl;
		std::cout << "- The target file is corrupted" << std::endl;
		std::cout << std::endl;
		std::cout << "Have you tried the following to resolve the issue:" << std::endl;
		std::cout << "- Check that the target file is in the input folder" << std::endl;
		std::cout << "- Check that the target file is a bitmap" << std::endl;
		std::cout << "- Check that the target file is not corrupted" << std::endl;
		std::cout << std::endl;
	}
	else
	{
		ifs.read((char*)&header_size, 4);
		ifs.read(header_unused, 4);
		ifs.read((char*)&header_offset, 4);

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

		m_image->setID(id);
		m_image->setSizeOfBitmap(header_size);
		m_image->setOffset(header_offset);
	}
}

/*
				 [::]===========================================================[::]
	 /M\         <|| /\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ||>         /M\
   <|[o]|00===00<<|| ++++++++++++++++ - Parses the DIB header - ++++++++++++++++ ||>>00===00|[o]|>
	 \W/         <|| \/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ ||>         \W/
				 [::]===========================================================[::]
*/
void BitmapParser::parseDIB(const std::string& filename)
{
	std::ifstream ifs(filename, std::ios::binary);

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

	ifs.read(skip_header, 14);
	delete skip_header;

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

	int offset = m_image->getOffset();
	if (offset > 54)
	{
		offset -= 54;
		int buffer;
		for (int i = 0; i < offset; i++)
		{
			ifs.read((char*)&buffer, 1);
			m_image->addBlanks(buffer);
			buffer = 0;
		}
	}

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


//                 [::]==================================================================================[::]
//     /M\         <|| /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ||>         /M\
//   <|[o]|00===00<<|| ++++++++++++++++ - Parses the pixel array for each colour depth - ++++++++++++++++ ||>>00===00|[o]|>
//     \W/         <|| \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ ||>         \W/
//                 [::]==================================================================================[::]
void BitmapParser::parsePixelArray(const std::string& filename)
{
	std::ifstream ifs(filename, std::ios::binary);

	int skip = m_image->getOffset();
	char * skip_header = new char[skip];
	ifs.read(skip_header, skip);
	delete skip_header, skip;
	int pad = 0;
	int t = 0;
	int bit = m_image->getBits();
	int width = m_image->getWidth();
	int height = m_image->getHeight();
	int pixelNum = width*height;
	std::cout << "|| Pixel Array ||" << std::endl;
	std::cout << "Pixels to process: " << pixelNum << std::endl;
	std::cout << "Processing..." << '\r';
	switch (bit)
	{
	case 32:
	{
		int blueBuffer;
		int greenBuffer;
		int redBuffer;
		int alphaBuffer;
		while (!ifs.eof())
		{
			progressAnimation();
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

		std::cout << "Processing completed!                              " << std::endl;
		std::cout << std::endl;

		m_image->setPadding(0);
		break;
	}
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
			progressAnimation();
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
		std::cout << "Processing completed!                              " << std::endl;
		std::cout << std::endl;

		m_image->setPadding(padding);
		break;
	}
	case 16:
	{
		int firstIndex;
		int secondIndex;
		int pixelBuffer;

		while (!ifs.eof())
		{
			progressAnimation();
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
			if (ifs.eof()) break;
			firstIndex = pixelBuffer & 0xF0;
			firstIndex = firstIndex >> 4;
			secondIndex = pixelBuffer & 0x0F;
			secondIndex = secondIndex >> 0;
			m_image->add2r(firstIndex);
			m_image->addAlpha(secondIndex);
			pixelBuffer = 0;
		}
		std::cout << "Processing completed!                              " << std::endl;
		std::cout << std::endl;
		m_image->setPadding(0);
		break;
	}
	case 8:
	{
		int padRemainder = (m_image->getWidth() % 4);
		int padding = (4 - padRemainder);
		if (padding == 4) padding = 0;
		int pixelBuffer;
		while (!ifs.eof())
		{
			progressAnimation();
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
		std::cout << "Processing completed!                              " << std::endl;
		std::cout << std::endl;
		m_image->setPadding(padding);
		break;
	}
	case 4:
	{
		/*
		//determining how much padding there is that needs to be skipped in order to read the pixel array correctly
		int padRemainder = ((m_image->getWidth() / 2) % 4);
		int padding = (4 - padRemainder);
		if (padding == 4) padding = 0;

		//defining a temporary buffer to store the pixel data
		int pixelBuffer;
		int firstIndex;
		int secondIndex;

		//loop through the pixel array until the end of the file
		while (!ifs.eof())
		{
			//if padding is required
			if (padding > 0)
			{
				//if it has reached the end of the row
				if (t == m_image->getWidth())
				{
					//loop until the padding has been skipped
					for (int i = 0; i < padding;i++)
					{
						ifs.read((char*)&pad, 1);
						pad = 0;
					}
					t = 0;
				}
			}
			//read the pixel data into the buffer, or in this case, 2 pixels worth of data
			ifs.read((char*)&pixelBuffer, 1);
			//if it has reached the end of the file, break out of the loop
			if (ifs.eof()) break;
			//extracts the last 4 bits from the byte
			firstIndex = pixelBuffer & 0xF0;
			firstIndex = firstIndex >> 4;
			//extracts the first 4 bits from the byte
			secondIndex = pixelBuffer & 0x0F;
			secondIndex = secondIndex >> 0;
			//stores both pixel data into the class variables
			m_image->addPixel4(firstIndex);
			m_image->addPixel4(secondIndex);
			t++;
		}
		*/
		int buffer = 0;
		while (!ifs.eof())
		{
			progressAnimation();
			ifs.read((char*)&buffer, 1);
			if (ifs.eof()) break;
			m_image->addPixel4(buffer);
			buffer = 0;
		}
		std::cout << "Processing completed!                              " << std::endl;
		std::cout << std::endl;
		break;
	}
	default:
		std::cout << "BitmapParser is unable to determine the file's properties, please try another file." << std::endl;
		break;
	}
}
