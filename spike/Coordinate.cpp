#include "Coordinate.h"

Coordinate::Coordinate(const int & newX, const int & newY)
{
	this->mXCoord = newX;
	this->mYCoord = newY;
}

int Coordinate::getXCoord() const
{
	return this->mXCoord;
}

int Coordinate::getYCoord() const
{
	return this->mYCoord;
}

void Coordinate::setXCoord(const int & newX)
{
	this->mXCoord = newX;
}

void Coordinate::setYCoord(const int & newY)
{
	mYCoord = newY;
}
