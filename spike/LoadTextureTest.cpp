#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"

using std::cout;
using std::endl;

// Animation help from: https://www.gamefromscratch.com/post/2015/10/26/SFML-CPP-Tutorial-Spritesheets-and-Animation.aspx

int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 500), "Ultimate Battleship");

	
    // Load Texture from File
	sf::Texture test = sf::Texture{};
	try {
		test.loadFromFile("assets/SplashAnimation.png");
	}
	catch (const std::exception &e) {
		std::cerr << e.what();

	}
	catch (...) {
		std::cerr << "unexpected error";
	}

    // Create Animation object using texture
	Animation test1(test);


    // (Optional) Scale up the animation so you can see it better
    test1.scale(sf::Vector2f(5,5));
    
    // Clock to keep track of time for animation 
    sf::Clock gameClock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}	
		window.clear();

        // When the clock reaches a certain time, change the frame of the animation 
        // and reset the clock. Changing the value its compared to will change the framerate
        if (gameClock.getElapsedTime().asSeconds() > .2)
        {
            test1.changeFrame();
            gameClock.restart();
        }

        // Display animation in its current state
		window.draw(test1);


		window.display();
	}


	return 0;
}