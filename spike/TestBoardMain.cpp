#include <SFML/Graphics.hpp>
#include "Board.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Test Window");

	Tile test1(sf::Vector2f(100, 100), sf::Color::Red, sf::Vector2f(250, 250));
	Board test2(sf::Color::Red);

	test2.getTileNum(2, 2).setIsOccupied(true);
	test2.getTileNum(2, 3).setIsOccupied(true);
	test2.getTileNum(2, 4).setIsOccupied(true);


	bool upPressed = false, rightPressed = false, downPressed = false, leftPressed = false, enterPressed = false;

	sf::Sprite test3;
	
	test3.setPosition(sf::Vector2f(10, 10));

	sf::Texture testTex;

	//testTex.loadFromFile("RedSubmarine.png");

	//test3.setTexture(testTex);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		window.clear();

		//window.draw(test1);

		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				window.draw(test2.getTileNum(i, j));
			}
		}

		//window.draw(test3);


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			upPressed = true;
		}
		else
		{
			if (upPressed == true)
			{
				test2.updateHighlight(test2.getCurXPos(), test2.getCurYPos() - 1);
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
				test2.updateHighlight(test2.getCurXPos(), test2.getCurYPos() + 1);
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
				test2.updateHighlight(test2.getCurXPos() + 1, test2.getCurYPos());
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
				test2.updateHighlight(test2.getCurXPos() - 1, test2.getCurYPos());
				leftPressed = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			enterPressed = true;
		}
		else
		{
			if (enterPressed == true)
			{
				test2.fire(test2.getCurXPos(), test2.getCurYPos());
				enterPressed = false;
			}
		}

		window.display();

	
	}

	return 0;
}