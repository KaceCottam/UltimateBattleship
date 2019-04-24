#include "Tile.h"

int Tile::getOccupationType() const { return mTileStatus; }

void Tile::setTileOccupation(const int& newOccupation) {
  mTileStatus = newOccupation;
  if (newOccupation != 0) setFillColor(sf::Color::Magenta);
}