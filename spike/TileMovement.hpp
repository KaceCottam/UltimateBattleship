#pragma once
#include "Board.h"
#include <SFML/Graphics.hpp>

enum Orientation
{
	HORIZONTAL, VERTICAL
};

void singleHighlight(Board &playerBoard, bool &upPressed, bool &downPressed, bool &rightPressed, bool &leftPressed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		upPressed = true;
	}
	else
	{
		if (upPressed == true)
		{
			playerBoard.updateHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() - 1);
			upPressed = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		downPressed = true;
	}
	else
	{
		if (downPressed == true)
		{
			playerBoard.updateHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + 1);
			downPressed = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rightPressed = true;
	}
	else
	{
		if (rightPressed == true)
		{
			playerBoard.updateHighlight(playerBoard.getCurXPos() + 1, playerBoard.getCurYPos());
			rightPressed = false;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		leftPressed = true;
	}
	else
	{
		if (leftPressed == true)
		{
			playerBoard.updateHighlight(playerBoard.getCurXPos() - 1, playerBoard.getCurYPos());
			leftPressed = false;
		}
	}
}

void numHighlight(Board &playerBoard, bool &upPressed, bool &downPressed, bool &rightPressed, bool &leftPressed, bool &rPressed,
	int &curOrientation, int shipLength)
{
	int curX = playerBoard.getCurXPos();
	int curY = playerBoard.getCurYPos();

	// UP
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		upPressed = true;
	}
	else
	{
		if (upPressed == true)
		{
			if (curOrientation == HORIZONTAL)
			{
				playerBoard.resetHighlight();
				playerBoard.updateHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() - 1);
				//playerBoard.updateSecondaryHighlight(5, 5);
				for (int count = 1; count < shipLength; ++count)
				{
					//playerBoard.updateSecondaryHighlight(5, 5);
					playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
				}
			}
			else
			{
				if (playerBoard.getCurYPos() != 0)
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() - 1);

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
					}
				}
				else
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(playerBoard.getCurXPos(), 10 - shipLength);

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
					}
				}
			}
			upPressed = false;
		}
	}
	
	
	// DOWN
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		downPressed = true;
	}
	else
	{
		if (downPressed == true)
		{
			if (curOrientation == HORIZONTAL)
			{
				playerBoard.resetHighlight();
				playerBoard.updateHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + 1);
			
				for (int count = 1; count < shipLength; ++count)
				{
					playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
				}
			}
			else // VERTICAL
			{
				if (playerBoard.getCurYPos() + shipLength < 10)
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + 1);

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
					}
				}
				else
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(playerBoard.getCurXPos(), 0);

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
					}
				}
			}
			
			//playerBoard.updateHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + 1);
			downPressed = false;
		}
	}
	
	// RIGHT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rightPressed = true;
	}
	else
	{
		if (rightPressed == true)
		{
			if (curOrientation == HORIZONTAL)
			{
				if (playerBoard.getCurXPos() + shipLength < 10)
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(playerBoard.getCurXPos() + 1, playerBoard.getCurYPos());

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
					}
				}
				else
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(0, playerBoard.getCurYPos());

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
					}
				}
			}
			else
			{
				playerBoard.resetHighlight();
				playerBoard.updateHighlight(playerBoard.getCurXPos() + 1, playerBoard.getCurYPos());

				for (int count = 1; count < shipLength; ++count)
				{
					playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
				}

			}
			rightPressed = false;
		}
	}
	
	
	// LEFT
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		leftPressed = true;
	}
	else
	{
		if (leftPressed == true)
		{
			if (curOrientation == HORIZONTAL)
			{
				if (playerBoard.getCurXPos() != 0)
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(playerBoard.getCurXPos() - 1, playerBoard.getCurYPos());

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
					}
				}
				else
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(10 - shipLength, playerBoard.getCurYPos());

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
					}
				}
			}
			else
			{
				playerBoard.resetHighlight();
				playerBoard.updateHighlight(playerBoard.getCurXPos() - 1, playerBoard.getCurYPos());

				for (int count = 1; count < shipLength; ++count)
				{
					playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
				}
			}




			leftPressed = false;
		}
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // ROTATIONS
	{
		rPressed = true;
	}
	else
	{
		if (rPressed == true)
		{
			if (curOrientation == HORIZONTAL)
			{
				curOrientation = VERTICAL;
				if (playerBoard.getCurYPos() + shipLength < 10)
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos());

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
					}
				}
				else
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(playerBoard.getCurXPos(), 0);

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos() + count);
					}
				}
			}
			else
			{
				curOrientation = HORIZONTAL;
				if (playerBoard.getCurXPos() + shipLength < 10)
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(playerBoard.getCurXPos(), playerBoard.getCurYPos());

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
					}
				}
				else
				{
					playerBoard.resetHighlight();
					playerBoard.updateHighlight(0, playerBoard.getCurYPos());

					for (int count = 1; count < shipLength; ++count)
					{
						playerBoard.updateSecondaryHighlight(playerBoard.getCurXPos() + count, playerBoard.getCurYPos());
					}
				}
			}

			rPressed = false;
		}
	}
	
}