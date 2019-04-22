#pragma once
#include <array>
#include <SFML/Graphics.hpp>
// #include "Coordinate.hpp" // we don't have to make the coordinate by ourselves,
                             // but still look at the changes i made to it.
/*
 * We can make the ship using an array, since we can know how big it is at compile
 * time.
 */

using std::array;

// a helper struct that contains coordinates and if the coordinate is hit.
// Also contains the sprite that goes with the ship.
struct ShipNode {
  sf::Vector2u coord; // we dont have to make the coordinate by ourselves.
  bool hit;
  sf::Sprite associated_sprite;
};

template<int Size> // We can make this a template for easier initialization.
class Ship : sf::Drawable // Making the ship drawable.
{
public:
  //Ship(const int &newPlayer = 0); // We do not need to check
                                      // which player's ship this is, because
                                      // it will be determined by the state of
                                      // the game. i.e. If we are attacking, it
                                      // will be the enemy player's ship without
                                      // a doubt.

  // virtual void sinkShip() = 0; This will be the same among all base classes,
  //                              so it does not need to be overrided.

  Ship(const array<sf::Vector2u, Size> &locations) : locations_{locations} {}

  bool getIsSunk() const {
          // This uses a little bit of "functional programming".
          // The [](){} construct is called a lambda, but you can call it an
          // "inline function". [] defines the lambda and the context, in this
          // case, I am taking in everything in the current scope (of the class)
          // by reference. In the parenthesis is a parameter, and finally there
          // is the function block in the curly braces.
          return std::count_if(locations_.begin(), locations_.end(),
                               [&](ShipNode i) { return i.hit; }) == Size;
  }

  // This is called a constant expression. It can be discovered at compile time and is
  // faster.
  constexpr int getSize() { return Size; }
  array<ShipNode, Size> getLocations() const {return locations_;}

  // void setIsSunk(const bool &newSunk); do not need this for the same reason
  // as
  //                                      not needing the variable
  // void setSize(const int &newSize); not needed because initialized at runtime

  // this will be set initialization.
  // void setLocations(const array<Coordinate, Size> &newLocations);

  // void setPlayer(const int &newPlayer); not needed as the player will never
  //                                       need to be changed

  // because we want to draw the ships, we can implement sf::Drawable.
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override
  {
    for(ShipNode &i : locations_) {
      target.draw(i.associated_sprite);
    }
  }
protected:
  // bool mIsSunk; we will not need this varaible as getIsSumk() can check this 
  //               for us.
  // int mSize; the array can keep track of the size.
  // int mPlayer;
  array<ShipNode, Size> locations_;
};

/*
 * Notice how all of the classes below are basically the same. With the size
 * compiled at runtime, we can use something called a typedef.
 */
using Carrier = Ship<5>;
using Battleship = Ship<4>;
using Cruiser = Ship<3>;
using Submarine = Ship<3>;
using Destroyer = Ship<2>;

/*
 * what we can do, is create a helper class that is a "ship builder" which automatically
 * rotates the sprites and sets them for us. This will get initialized on the heap
 * when we load all of the assets.
 */

/*
class Carrier : public Ship<5>
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
*/