#pragma once
#include <array>
#include <SFML/Graphics.hpp>

using std::array;

struct ShipNode {
  sf::Vector2u coord;
  bool hit;
  sf::Sprite associated_sprite;
};

template<int Size>
class Ship : sf::Drawable
{
public:
  Ship(const array<sf::Vector2u, Size> &locations) : locations_{locations} {}

  bool getIsSunk() const {
          return std::count_if(locations_.begin(), locations_.end(),
                               [&](ShipNode i) { return i.hit; }) == Size;
  }

  constexpr int getSize() { return Size; }

  array<ShipNode, Size> getLocations() const {return locations_;}

  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override
  {
    for(ShipNode &i : locations_) {
      target.draw(i.associated_sprite);
    }
  }
protected:
  array<ShipNode, Size> locations_;
};

using Carrier = Ship<5>;
using Battleship = Ship<4>;
using Cruiser = Ship<3>;
using Submarine = Ship<3>;
using Destroyer = Ship<2>;