#pragma once
#include <vector>
#include "Coordinate.hpp"

using std::vector;

class Ship
{
public:
	Ship(const int &newPlayer = 0);

	virtual void sinkShip() = 0;

	bool getIsSunk() const;
	int getSize() const;
	vector<Coordinate> getLocations() const;
	int getPlayer() const;

	void setIsSunk(const bool &newSunk);
	void setSize(const int &newSize);
	void setLocations(const vector<Coordinate> &newLocations);
	void setPlayer(const int &newPlayer);

protected:
	bool mIsSunk;
	int mSize;
	int mPlayer;
	vector<Coordinate> mLocations;
};

class Carrier : public Ship
{
public:
	Carrier(const Coordinate &coord1 = Coordinate(0,0), const Coordinate &coord2 = Coordinate(0,0), 
		const Coordinate &coord3 = Coordinate(0,0), const Coordinate &coord4 = Coordinate(0,0),
		const Coordinate &coord5 = Coordinate(0,0), const int &newPlayer = 0) : Ship(newPlayer)
	{
		mLocations.push_back(coord1);
		mLocations.push_back(coord2);
		mLocations.push_back(coord3);
		mLocations.push_back(coord4);
		mLocations.push_back(coord5);
		mSize = 5;
	};

	void sinkShip();
	void setLocations(const Coordinate &coord1, const Coordinate &coord2, const Coordinate &coord3,
		const Coordinate &coord4, const Coordinate &coord5);
};

class Battleship : public Ship
{
public:
	Battleship(const Coordinate &coord1 = Coordinate(0, 0), const Coordinate &coord2 = Coordinate(0, 0),
		const Coordinate &coord3 = Coordinate(0, 0), const Coordinate &coord4 = Coordinate(0, 0),
		const int &newPlayer = 0) : Ship(newPlayer)
	{
		mLocations.push_back(coord1);
		mLocations.push_back(coord2);
		mLocations.push_back(coord3);
		mLocations.push_back(coord4);
		mSize = 4;
	};

	void sinkShip();
	void setLocations(const Coordinate &coord1, const Coordinate &coord2, const Coordinate &coord3,
		const Coordinate &coord4);
};

class Size3Ship : public Ship
{
public:
	Size3Ship(const Coordinate &coord1 = Coordinate(0, 0), const Coordinate &coord2 = Coordinate(0, 0),
		const Coordinate &coord3 = Coordinate(0, 0), const int &newPlayer = 0) : Ship(newPlayer)
	{
		mLocations.push_back(coord1);
		mLocations.push_back(coord2);
		mLocations.push_back(coord3);
		mSize = 3;
	};

	virtual void sinkShip() = 0;

	void setLocations(const Coordinate &coord1, const Coordinate &coord2, const Coordinate &coord3);

};

class Cruiser : public Size3Ship
{
public:

	Cruiser(const Coordinate &coord1 = Coordinate(0, 0), const Coordinate &coord2 = Coordinate(0, 0),
		const Coordinate &coord3 = Coordinate(0, 0), const int &newPlayer = 0) : Size3Ship(coord1, coord2, coord3, newPlayer) {};

	void sinkShip();
};

class Submarine : public Size3Ship
{
public:
	Submarine(const Coordinate &coord1 = Coordinate(0, 0), const Coordinate &coord2 = Coordinate(0, 0),
		const Coordinate &coord3 = Coordinate(0, 0), const int &newPlayer = 0) : Size3Ship(coord1, coord2, coord3, newPlayer) {};

	void sinkShip();
};

class Destroyer : public Ship
{
public:
	Destroyer(const Coordinate &coord1 = Coordinate(0, 0), const Coordinate &coord2 = Coordinate(0, 0),
		const int &newPlayer = 0) : Ship(newPlayer)
	{
		mLocations.push_back(coord1);
		mLocations.push_back(coord2);
	};

	void sinkShip();

	void setLocations(const Coordinate &coord1, const Coordinate &coord2);
};