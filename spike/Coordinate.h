#pragma once

class Coordinate
{
public:
	Coordinate(const int &newX = 0, const int &newY = 0);

	int getXCoord() const;
	int getYCoord() const;

	void setXCoord(const int &newX);
	void setYCoord(const int &newY);

private:
	int mXCoord;
	int mYCoord;
};