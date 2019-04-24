#include <SFML/Graphics.hpp>
#include "Board.h"
#include "TileMovement.hpp"
#include "ShipPlacement.hpp"
#include "FiringMechanism.hpp"
#include "Animation.h"
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Ultimate Battleship");

	sf::Texture splashTexture = sf::Texture{};
	try {
		splashTexture.loadFromFile("SplashAnimation.png");
	}
	catch (const std::exception &e) {
		std::cerr << e.what();

	}
	catch (...) {
		std::cerr << "unexpected error";
	}

	sf::Texture explosionTexture = sf::Texture{};
	try {
		explosionTexture.loadFromFile("ExplosionAnimation.png");
	}
	catch (const std::exception &e) {
		std::cerr << e.what();

	}
	catch (...) {
		std::cerr << "unexpected error";
	}

	Animation splashAnimation(splashTexture);
	Animation explosionAnimation(explosionTexture);
	splashAnimation.scale(sf::Vector2f(5,5));
	explosionAnimation.scale(sf::Vector2f(5,5));
	sf::Clock gameClock;

	Board playBoard[2] = { Board(sf::Color::Blue), Board(sf::Color::Red) };

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
			for (int i = 0; i < 10; ++i)
			{
				for (int j = 0; j < 10; ++j)
				{
					window.draw(playBoard[isPlayer1].getTileNum(i, j));
				}
			}
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
							auto placement_rect = 
									playBoard[isPlayer1]
										.getTileNum(playBoard[isPlayer1].getCurYPos(),
													playBoard[isPlayer1].getCurXPos())
										.getGlobalBounds();

								sf::Transform animationTransform;
								animationTransform.translate({placement_rect.left - 20, placement_rect.top - 20});
							if (fireStatus == HIT)
							{
								
								while (explosionAnimation.getCurFrame() < 9)
								{
									if (gameClock.getElapsedTime().asSeconds() > .2)
        							{
										explosionAnimation.changeFrame();
          								gameClock.restart();
        							}
																		
									window.draw(explosionAnimation, animationTransform);
									window.display();
								}
								explosionAnimation.resetFrame();
								bool newShipSunk = playBoard[isPlayer1].updateFleetStatus();
								if (newShipSunk)
								{
									isWinner = playBoard[isPlayer1].isWinner();
								}
							}
							else
							{
								while (splashAnimation.getCurFrame() < 9)
								{
									if (gameClock.getElapsedTime().asSeconds() > .2)
        							{
										splashAnimation.changeFrame();
          								gameClock.restart();
        							}
									window.draw(splashAnimation, animationTransform);
									window.display();
								}
								splashAnimation.resetFrame();
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

//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(500, 500), "Ultimate Battleship");
//
//	//Tile test1;
//
//	sf::Texture test = sf::Texture{};
//	try {
//		test.loadFromFile("RoundButton1.png");
//	}
//	catch (const std::exception &e) {
//		std::cerr << e.what();
//
//	}
//	catch (...) {
//		std::cerr << "unexpected error";
//	}
//
//	sf::Sprite s1{ test};
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}	
//		window.clear();
//
//		window.draw(s1);
//
//		window.display();
//	}
//
//
//	return 0;
//}