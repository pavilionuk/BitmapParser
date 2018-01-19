#include "stdafx.h"
#include "BitmapParser.h"

int main(int argc, _TCHAR* argv[])
{
	std::string filename("lel3.bmp");
	//std::string filename2("aaaaaaAAAAAAAAAAHHHH.bmp");
	BitmapParser* parser = new BitmapParser(filename);
	//BitmapParser* create = new BitmapParser(filename2);
	
	
	
	
	
	
	
	delete parser;
	//delete create;

	//Have the lambs stopped screaming Clarice?
	return 0;
}