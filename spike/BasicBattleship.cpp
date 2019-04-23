#include <SFML/Graphics.hpp>
#include "Board.h"
#include "TileMovement.hpp"
#include "ShipPlacement.hpp"
#include "FiringMechanism.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
  sf::RenderWindow window(sf::VideoMode(500, 500), "Ultimate Battleship");

  /*Board player1Board(sf::Color::Red);
  Board player2Board(sf::Color::Blue);*/

  Board playBoard[2] = { Board(sf::Color::Blue), Board(sf::Color::Red) };

  // ? Do we need this? we can use a static variable inside the function to keep track of change.
  bool upPressed = false, rightPressed = false, downPressed = false, leftPressed = false, rPressed = false, enterPressed = false;
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
    }
    
    window.clear();
    
    if (isShipPlacement)
    {
      window.draw(playBoard[isPlayer1]);
      numHighlight(playBoard[isPlayer1], upPressed, downPressed, rightPressed, leftPressed, rPressed, curOrientation, curShipLength);

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
      {
        enterPressed = true;
      }
      else
      {
        if (enterPressed == true)
        {
          placeShip(playBoard[isPlayer1], curShip, curShipLength, curOrientation, isPlayer1, isShipPlacement);
          enterPressed = false;
        }
      }
    }
    else if (!isWinner) // GAMEPLAY
    {
      bool waitingEnter = false;
      int fireStatus = INVALID;

      if (firstTurn)
      {
        playBoard[0].resetHighlight();
        playBoard[0].resetFill();
        playBoard[1].resetHighlight();
        playBoard[1].resetFill();
        firstTurn = false;
      }

      for (int i = 0; i < 10; ++i)
      {
        for (int j = 0; j < 10; ++j)
        {
          window.draw(playBoard[isPlayer1].getTileNum(i, j));
        }
      }
      singleHighlight(playBoard[isPlayer1], upPressed, downPressed, rightPressed, leftPressed);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
      {
        enterPressed = true;
      }
      else
      {
        if (enterPressed == true)
        {
          if (!waitingEnter)
          {
            fireStatus = fire(playBoard[isPlayer1]);
            if (fireStatus != INVALID)
            {
              waitingEnter = true;
              if (fireStatus == HIT)
              {
                bool newShipSunk = playBoard[isPlayer1].updateFleetStatus();
                if (newShipSunk)
                {
                  //cout << "NEW SHIP SUNK" << endl;
                  isWinner = playBoard[isPlayer1].isWinner();
                }
              }
              if (isPlayer1)
              {
                isPlayer1 = false;
              }
              else
              {
                isPlayer1 = true;
              }
            }
          }
          else
          {
            waitingEnter = false;
            isPlayer1 = false;
          }
          enterPressed = false;
        }
      }
      
    }
    else
    {
      if (isWinner)
      {
        cout << "PLAYER " << isPlayer1 + 1 << "WINS!" << endl;
      }
    }

    window.display();

  
  }

  return 0;
}