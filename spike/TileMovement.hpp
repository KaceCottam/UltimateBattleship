#pragma once
#include <SFML/Graphics.hpp>
#include "Board.h"

// If the ships are being placed horizontally or vertically
enum Orientation { HORIZONTAL, VERTICAL };

// Highlights one block - used for firing at ships
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

// Highlights a number of blocks based on ship length
void numHighlight(Board &playerBoard, const sf::Event &e, int &curOrientation,
                  int shipLength) {
  int curX = playerBoard.getCurXPos();
  int curY = playerBoard.getCurYPos();

  // UP
  if (e.type == sf::Event::KeyReleased) {
    if (e.key.code == sf::Keyboard::Up) {
      if (curOrientation == HORIZONTAL) { // Horizontal
        playerBoard.resetHighlight(); // Clears previous highlights
        playerBoard.updateHighlight(playerBoard.getCurXPos(), // updates main highlight (where the "cursor" is)
                                    playerBoard.getCurYPos() - 1);
        // updates the other tiles (the ones that aren't considered to be the current "cursor" location)
        for (int count = 1; count < shipLength; ++count) {
          playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count,
                                               playerBoard.getCurYPos());
        }
      } else { // Vertical - makes sure that the highlight doesn't wrap around
        if (playerBoard.getCurYPos() != 0) { // it isn't at the top - only needs to move 1 tile
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                      playerBoard.getCurYPos() - 1);

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
          }
        } else { // it is at the top - needs to be moved more than one tile so highlight doesn't wrap
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
        if (playerBoard.getCurYPos() + shipLength < 10) { // not at bottom
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                      playerBoard.getCurYPos() + 1);

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
          }
        } else { // at bottom
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
      if (curOrientation == HORIZONTAL) { // Horizontal
        if (playerBoard.getCurXPos() + shipLength < 10) { // not at far right
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos() + 1,
                                      playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        } else { // at far right
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(0, playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        }
      } else { // Vertical
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
      if (curOrientation == HORIZONTAL) { // Horizontal
        if (playerBoard.getCurXPos() != 0) { // not at far left
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos() - 1,
                                      playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        } else { // at far left
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(10 - shipLength,
                                      playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) {
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        }
      } else { // Vertical
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
      if (curOrientation == HORIZONTAL) { // Switch from horizontal to vertical
        curOrientation = VERTICAL;
        if (playerBoard.getCurYPos() + shipLength < 10) { // not too close to edge of board
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                      playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) { // switch highlight to vertical
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
          }
        } else { // too close to edge of board - reset y to 0
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(), 0);

          for (int count = 1; count < shipLength; ++count) { // switch highlight to verical
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
          }
        }
      } else { // switch from vertical to horiontal
        curOrientation = HORIZONTAL;
        if (playerBoard.getCurXPos() + shipLength < 10) { // not too close to edge of board
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(playerBoard.getCurXPos(),
                                      playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) { // switch highlight to horizontal
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        } else { // too close to edge of board
          playerBoard.resetHighlight();
          playerBoard.updateHighlight(0, playerBoard.getCurYPos());

          for (int count = 1; count < shipLength; ++count) { // switch highlight to horizontal
            playerBoard.updateSecondaryHighlight(
                playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
          }
        }
      }
    }
  }
}