#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

enum Orientation { HORIZONTAL, VERTICAL };

void singleHighlight(Board &playerBoard, const sf::Event &e) {
  if (e.type == sf::Event::KeyReleased) {
    if (e.key.code == sf::Keyboard::Up) {
      playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                  playerBoard.getCurYPos() - 1);
    }
    if (e.key.code == sf::Keyboard::Down) {
      playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                  playerBoard.getCurYPos() + 1);
    }
    if (e.key.code == sf::Keyboard::Right) {
      playerBoard.updateHighlight(playerBoard.getCurXPos() + 1,
                                  playerBoard.getCurYPos());
    }
    if (e.key.code == sf::Keyboard::Left) {
      playerBoard.updateHighlight(playerBoard.getCurXPos() - 1,
                                  playerBoard.getCurYPos());
    }
  }
}

void numHighlight(Board &playerBoard, const sf::Event &e, int &curOrientation,
                  int shipLength) {
  int curX = playerBoard.getCurXPos();
  int curY = playerBoard.getCurYPos();

  // UP
  if (e.type == sf::Event::KeyReleased) {
    if (e.key.code == sf::Keyboard::Up) {
      if (curOrientation == HORIZONTAL) {
        playerBoard.resetHighlight();
        playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                    playerBoard.getCurYPos() - 1);
        // playerBoard.updateSecondaryHighlight(5, 5);
        for (int count = 1; count < shipLength; ++count) {
          // playerBoard.updateSecondaryHighlight(5, 5);
          playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count,
                                               playerBoard.getCurYPos());
        }
      } else {
        if (playerBoard.getCurYPos() != 0) {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                      playerBoard.getCurYPos() - 1);

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
          }
        } else {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                      10 - shipLength);

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
          }
        }
      }
    }

    // DOWN
    if (e.key.code == sf::Keyboard::Down) {
      if (curOrientation == HORIZONTAL) {
        playerBoard.resetHighlight();
        playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                    playerBoard.getCurYPos() + 1);

        for (int count = 1; count < shipLength; ++count) {
          playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count,
                                               playerBoard.getCurYPos());
        }
      } else  // VERTICAL
      {
        if (playerBoard.getCurYPos() + shipLength < 10) {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                      playerBoard.getCurYPos() + 1);

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
          }
        } else {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(), 0);

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
          }
        }
      }
    }

    // RIGHT
    if (e.key.code == sf::Keyboard::Right) {
      if (curOrientation == HORIZONTAL) {
        if (playerBoard.getCurXPos() + shipLength < 10) {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos() + 1,
                                      playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        } else {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(0, playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        }
      } else {
        playerBoard.resetHighlight();
        playerBoard.updateHighlight(playerBoard.getCurXPos() + 1,
                                    playerBoard.getCurYPos());

        for (int count = 1; count < shipLength; ++count) {
          playerBoard.updateSecondaryHighlight(
              playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
        }
      }
    }

    // LEFT
    if (e.key.code == sf::Keyboard::Left) {
      if (curOrientation == HORIZONTAL) {
        if (playerBoard.getCurXPos() != 0) {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos() - 1,
                                      playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        } else {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(10 - shipLength,
                                      playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        }
      } else {
        playerBoard.resetHighlight();
        playerBoard.updateHighlight(playerBoard.getCurXPos() - 1,
                                    playerBoard.getCurYPos());

        for (int count = 1; count < shipLength; ++count) {
          playerBoard.updateSecondaryHighlight(
              playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
        }
      }
    }

    if (e.key.code == sf::Keyboard::R)  // ROTATIONS
    {
      if (curOrientation == HORIZONTAL) {
        curOrientation = VERTICAL;
        if (playerBoard.getCurYPos() + shipLength < 10) {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                      playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
          }
        } else {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(), 0);

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
          }
        }
      } else {
        curOrientation = HORIZONTAL;
        if (playerBoard.getCurXPos() + shipLength < 10) {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                      playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        } else {
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(0, playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        }
      }
    }
  }
}