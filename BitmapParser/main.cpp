#include "stdafx.h"
#include "BitmapParser.h"
#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>

// #$pla$h Gang
//void justForFun() { while (true) { std::cout << "Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  " << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << "emes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  M" << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << "mes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Me" << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << "es  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Mem" << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << "s  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Meme" << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << "  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes" << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100));std::cout << " Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes  Memes " << '\r';std::this_thread::sleep_for(std::chrono::milliseconds(100)); } }


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
	remove(filename2.c_str());
	BitmapParser* parser = new BitmapParser(filename);
	delete parser;
	int b = 10;
	for (int i = 1;i<11;i++)
	{
		std::cout << "BitmapParser will terminate in: " << b << "  " << '\r';
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		b--;
	}
	//justForFun();
	//Have the lambs stopped screaming Clarice?
	return 0;
}