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
	m_width = width;
}

void BitmapImage::setHeight(const int & height)
{
	m_height = height;
}

void BitmapImage::setPlane(const int & plane)
{
	m_planes = plane;
}

void BitmapImage::setBits(const int & bits)
{
	m_bits = bits;
}

void BitmapImage::setPac(const int & pac)
{
	m_pac = pac;
}

void BitmapImage::setRaw(const int & raw)
{
	m_raw = raw;
}

void BitmapImage::setResW(const int & resW)
{
	m_resW = resW;
}

void BitmapImage::setResH(const int & resH)
{
	m_resH = resH;
}

void BitmapImage::setColours(const int & colours)
{
	m_colours = colours;
}

void BitmapImage::setiColours(const int & icolours)
{
	m_icolours = icolours;
}

int BitmapImage::getWidth()
{
	return m_width;
}

int BitmapImage::getHeight()
{
	return m_height;
}

int BitmapImage::getPlane()
{
	return m_planes;
}

int BitmapImage::getBits()
{
	return m_bits;
}

int BitmapImage::getPac()
{
	return m_pac;
}

int BitmapImage::getRaw()
{
	return m_raw;
}

int BitmapImage::getResW()
{
	return m_resW;
}

int BitmapImage::getResH()
{
	return m_resH;
}

int BitmapImage::getColours()
{
	return m_colours;
}

int BitmapImage::getiColours()
{
	return m_icolours;
}

void BitmapImage::add2b(int& pa_b)
{
	m_PA_b.push_back(pa_b);
}

void BitmapImage::add2g(int & pa_g)
{
	m_PA_g.push_back(pa_g);
}

void BitmapImage::add2r(int & pa_r)
{
	m_PA_r.push_back(pa_r);
}

void BitmapImage::setPadding(const int & padding)
{
	m_padding = padding;
}

std::vector<int> BitmapImage::getB()
{
	return m_PA_b;
}

std::vector<int> BitmapImage::getG()
{
	return m_PA_g;
}

std::vector<int> BitmapImage::getR()
{
	return m_PA_r;
}

int BitmapImage::getPadding()
{
	return m_padding;
}


