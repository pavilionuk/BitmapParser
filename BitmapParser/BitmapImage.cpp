#include "stdafx.h"
#include "BitmapImage.h"


BitmapImage::BitmapImage()
{
	

}

BitmapImage::~BitmapImage()
{
}

void BitmapImage::setID(const std::string & id)
{
	m_ID = id;
}

void BitmapImage::setSizeOfBitmap(const int & sizeOfBitmap)
{
	m_sizeOfBitmap = sizeOfBitmap;
}

void BitmapImage::setOffset(const int & offset)
{
	m_offset = offset;
}

int BitmapImage::getOffset()
{
	return m_offset;
}

std::string BitmapImage::getID()
{
	return m_ID;
}

int BitmapImage::getSizeOfBitmap()
{
	return m_sizeOfBitmap;
}

void BitmapImage::setBytes(const int & bytes)
{
	m_bytes = bytes;
}

int BitmapImage::getBytes()
{
	return m_bytes;
}

void BitmapImage::setWidth(const int & width)
{

}


