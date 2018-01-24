#include "stdafx.h"
#include "BitmapParser.h"
#include <stdio.h>
#include <iostream>

int main(int argc, _TCHAR* argv[])
{

	std::string path = R"(C:\Users\pavilion.sahota\Desktop\input\)";
	std::string filename;
	std::cout << "Please enter the filename (including file extention): ";
	std::cin >> filename;
	filename = path + filename;
	std::cout << std::endl;
	std::string filename2(R"(C:\Users\pavilion.sahota\Desktop\output\output.bmp)");
	remove(filename2.c_str());
	BitmapParser* parser = new BitmapParser(filename);
	
	
	
	
	
	
	
	delete parser;
	//delete create;
	//Have the lambs stopped screaming Clarice?
	return 0;
}