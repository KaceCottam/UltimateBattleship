#include "Board.h"
#include <functional>

void Board::updateHighlight(int x, int y) {
  x = abs(x % 10);
  y = abs(y % 10);

  mGrid[mCurYPos * 10 + mCurXPos].setOutlineColor(mColor);
  mCurXPos = x;
  mCurYPos = y;
  mGrid[mCurYPos * 10 + mCurXPos].setOutlineColor(sf::Color::Yellow);
}

void Board::updateSecondaryHighlight(int x, int y) {
  mGrid[x + y * 10].setOutlineColor(sf::Color::Yellow);
}

void Board::resetHighlight() {
  for (int i = 0; i < 100; ++i) {
      mGrid[i].setOutlineColor(mColor);
  }
}

void Board::resetFill() {
  for (int i = 0; i < 100; ++i) {
      mGrid[i].setFillColor(sf::Color::Transparent);
  }
}

int Board::getCurXPos() const { return mCurXPos; }

int Board::getCurYPos() const { return mCurYPos; }

bool Board::updateFleetStatus() {
  bool found = false;

  auto discover_sunk_ship =
      [&](const int currentSearch) {
        // Finds a ship if it is the same occupation type as the current search
        auto found_thing =
            std::find_if(mGrid.begin(), mGrid.end(), [&currentSearch](auto i) {
              if (i.getOccupationType() == currentSearch) return true;
              return false;
            });
        // If it can't find it in the grid, (ie it is a previous miss or hit)
        if (found_thing == mGrid.end()) {
          // If this ship is still considered alive, it is marked as sunk.
          if (mFleet[currentSearch] == true) {
            cout << "Ship Type: " << found_thing->getOccupationType() << " has been sunk!" << endl;
            mFleet[currentSearch] = false;
            return true;
          }
        }
        return false;
      };

  for(int i = TileOccupation::CARRIER; i <= TileOccupation::DESTROYER; ++i) {
    found = discover_sunk_ship(i-1);
    if(found) break;
  }
  return found;
}

bool Board::isWinner() const {
  bool winner = true;

  for (int count = 0; count < 5 && winner; ++count) {
    if (mFleet[count]) {
      winner = false;
    }
  }
  return winner;
}

Tile Board::getTileNum(int i, int j) const { return mGrid[i + j * 10]; }
