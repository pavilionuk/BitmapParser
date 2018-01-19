#include "stdafx.h"
#include "BitmapParser.h"

int main(int argc, _TCHAR* argv[])
{
	std::string filename("mr magoriums wonder emporium.bmp");
	BitmapParser* parser = new BitmapParser(filename);
	
	
	
	
	
	
	
	delete parser;
	return 0;
}