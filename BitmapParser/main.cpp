#include "stdafx.h"
#include "BitmapParser.h"
#include <stdio.h>

int main(int argc, _TCHAR* argv[])
{
	
	std::string filename(R"(C:\Users\pavilion.sahota\Desktop\input\top.bmp)");
	std::string filename2(R"(C:\Users\pavilion.sahota\Desktop\output\aaaaaaAAAAAAAAAAHHHH.bmp)");
	remove(filename2.c_str());
	BitmapParser* parser = new BitmapParser(filename);
	//BitmapParser* create = new BitmapParser(filename2);
	
	
	
	
	
	
	
	delete parser;
	//delete create;
	//Have the lambs stopped screaming Clarice?
	return 0;
}