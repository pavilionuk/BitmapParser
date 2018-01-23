#include "stdafx.h"
#include "BitmapParser.h"
#include <stdio.h>
#include <iostream>

int main(int argc, _TCHAR* argv[])
{
	typedef std::string str;
	str filename;
	std::cout << "Please enter the filename (including file extention): ";
	std::cin >> filename;
	std::cout << std::endl;
	str filename2("aaaaaaAAAAAAAAAAHHHH.bmp");
	remove(filename2.c_str());
	BitmapParser* parser = new BitmapParser(filename);
	//BitmapParser* create = new BitmapParser(filename2);
	
	
	
	
	
	
	
	delete parser;
	//delete create;
	//Have the lambs stopped screaming Clarice?
	return 0;
}