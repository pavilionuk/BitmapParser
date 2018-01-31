#include "stdafx.h"
#include "BitmapParser.h"
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>

// #$pla$h Gang
int main(int argc, _TCHAR* argv[])
{
	std::cout << "              [::]=============================================================[::]               " << std::endl;
	std::cout << R"(  /M\         <|| /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//\/\/\/\/\/\ ||>         /M\  )" << std::endl;
	std::cout << "<|[o]|00===00<<|| ++++++++++++++++ - Welcome to BitmapParser - ++++++++++++++++ ||>>00===00|[o]|>" << std::endl;
	std::cout << R"(  \W/         <|| \/\/\/\/\/\/\/\/\/\/\/\/\\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ ||>         \W/  )" << std::endl;
	std::cout << "              [::]=============================================================[::]               " << std::endl;
	std::string path = R"(C:\Users\pavilion.sahota\Desktop\input\)";
	std::string filename;
	std::cout << "Please enter the filename (including file extension): ";
	std::cin >> filename;
	filename = path + filename;
	std::cout << std::endl;
	std::string filename2(R"(C:\Users\pavilion.sahota\Desktop\output\output.bmp)");
	//remove(filename2.c_str());
	BitmapParser* parser = new BitmapParser(filename);
	delete parser;
	int b = 10;
	for (int i = 1;i<11;i++)
	{
		std::cout << "BitmapParser will terminate in: " << b << "  " << '\r';
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		b--;
	}
	return 0;
}