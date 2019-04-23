#include <iostream>
#include <queue>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "TileMovement.hpp"
#include "ShipPlacement.hpp"
#include "FiringMechanism.hpp"

using std::cout;
using std::endl;

int main()
{
  sf::RenderWindow window(sf::VideoMode(500, 500), "Ultimate Battleship");

  /*Board player1Board(sf::Color::Red);
  Board player2Board(sf::Color::Blue);*/

  Board playBoard[2] = { Board(sf::Color::Blue), Board(sf::Color::Red) };

  bool isShipPlacement = true;
  bool isPlayer1 = true;
  int curShip = CARRIER;
  int curShipLength = 5;
  int curOrientation = HORIZONTAL;
  bool firstTurn = true;
  bool isWinner = false;

  while (window.isOpen() && !isWinner)
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
      if (isShipPlacement) {
        window.draw(playBoard[isPlayer1]);
        numHighlight(playBoard[isPlayer1], event, curOrientation,
                     curShipLength);

        if (event.type == sf::Event::KeyReleased &&
            event.key.code == sf::Keyboard::Enter) {
          placeShip(playBoard[isPlayer1], curShip, curShipLength,
                    curOrientation, isPlayer1, isShipPlacement);
        }
      } else if (!isWinner)  // GAMEPLAY
      {
        bool waitingEnter = false;
        int fireStatus = INVALID;

        if (firstTurn) {
          playBoard[0].resetHighlight();
          playBoard[0].resetFill();
          playBoard[1].resetHighlight();
          playBoard[1].resetFill();
          firstTurn = false;
        }

        window.draw(playBoard[isPlayer1]);
        singleHighlight(playBoard[isPlayer1], event);
        if (event.type == sf::Event::KeyReleased &&
            event.key.code == sf::Keyboard::Enter) {
          if (!waitingEnter) {
            fireStatus = fire(playBoard[isPlayer1]);  // Firing mechanism.hpp
            if (fireStatus != INVALID) {
              waitingEnter = true;
              if (fireStatus == HIT) {
                bool newShipSunk = playBoard[isPlayer1].updateFleetStatus();
                if (newShipSunk) {
                  // cout << "NEW SHIP SUNK" << endl;
                  isWinner = playBoard[isPlayer1].isWinner();
                }
              }
              if (isPlayer1) {
                isPlayer1 = false;
              } else {
                isPlayer1 = true;
              }
            }
          } else {
            waitingEnter = false;
            isPlayer1 = false;
          }
        }

      } else {
        if (isWinner) {
          cout << "PLAYER " << isPlayer1 + 1 << "WINS!" << endl;
        }
      }
    }

    window.display();
  }

  return 0;
}