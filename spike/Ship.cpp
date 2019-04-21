#include "Ship.h"

Ship::Ship(const int &newPlayer = 0)
{
	mIsSunk = false;
	mPlayer = newPlayer;
}

bool Ship::getIsSunk() const
{
	return mIsSunk;
}

int Ship::getSize() const
{
	return mSize;
}

vector<Coordinate> Ship::getLocations() const
{
	return mLocations;
}

int Ship::getPlayer() const
{
	return mPlayer;
}

void Ship::setIsSunk(const bool & newSunk)
{
	mIsSunk = newSunk;
}

void Ship::setSize(const int & newSize)
{
	mSize = newSize;
}

void Ship::setLocations(const vector<Coordinate>& newLocations)
{
	mLocations = newLocations;
}

void Ship::setPlayer(const int & newPlayer)
{
	mPlayer = newPlayer;
}

void Carrier::sinkShip()
{
	mIsSunk = true;
	// message saying that Player x's Carrier has sunk
}

void Carrier::setLocations(const Coordinate & coord1, const Coordinate & coord2, const Coordinate & coord3, const Coordinate & coord4, const Coordinate & coord5)
{
	mLocations[0] = coord1;
	mLocations[1] = coord2;
	mLocations[2] = coord3;
	mLocations[3] = coord4;
	mLocations[4] = coord5;
}

void Battleship::sinkShip()
{
	mIsSunk = true;
	// message saying that Player x's Battleship has sunk
}

void Battleship::setLocations(const Coordinate & coord1, const Coordinate & coord2, const Coordinate & coord3, const Coordinate & coord4)
{
	mLocations[0] = coord1;
	mLocations[1] = coord2;
	mLocations[2] = coord3;
	mLocations[3] = coord4;
}

void Size3Ship::setLocations(const Coordinate & coord1, const Coordinate & coord2, const Coordinate & coord3)
{
	mLocations[0] = coord1;
	mLocations[1] = coord2;
	mLocations[2] = coord3;
}

void Cruiser::sinkShip()
{
	mIsSunk = true;
	// message saying player x's Cruiser has sunk
}

void Submarine::sinkShip()
{
	mIsSunk = true;
	// message saying player x's submarine has sunk
}

void Destroyer::sinkShip()
{
	mIsSunk = true;
	// message saying player x's Destroyer has sunk
}

void Destroyer::setLocations(const Coordinate & coord1, const Coordinate & coord2)
{
	mLocations[0] = coord1;
	mLocations[1] = coord2;
}
