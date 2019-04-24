#include "Tests.h"

#include "Board.h"
#include "FiringMechanism.hpp"
#include "ShipPlacement.hpp"
#include "TileMovement.hpp"
#include "Animation.h"

void Tests::testAnimationChangeFrame(void)
{
    sf::Texture testTexture;
    
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

    Animation explosionAnimation(testTexture);

    explosionAnimation.changeFrame();
    explosionAnimation.changeFrame();
    explosionAnimation.changeFrame();

    if (explosionAnimation.getCurFrame() == 3)
    {
        cout << "Test Animation Change Frame Passed!" << endl;
    }
    else
    {
        cout << "Test Animation Change Frame failed." << endl;
        cout << "Value for frame was supposed to be 3. Actual value was " << explosionAnimation.getCurFrame() << endl;
    }
}

void Tests::testUpdateFleetStatus(void)
{
    Board b(sf::Color::Red);

    // Mock set-up of ship placement
    b.getTileNum(1,1).setTileOccupation(CARRIER);
    b.getTileNum(1,2).setTileOccupation(BATTLESHIP);
    b.getTileNum(1,3).setTileOccupation(CRUISER);
    b.getTileNum(1,4).setTileOccupation(SUBMARINE);
    b.getTileNum(1,5).setTileOccupation(DESTROYER);

    // Should detect that all ships are still present - expect false
    bool newShipDestroyed1 = b.updateFleetStatus();

    // simulate destruction of carrier
    b.getTileNum(1,1).setTileOccupation(PREV_HIT);

    // Should detect that a new ship was destroyed - expect true
    bool newShipDestroyed2 = b.updateFleetStatus();
    
    // Shouldn't detect any changes - expect false
    bool newShipDestroyed3 = b.updateFleetStatus();

    if (!newShipDestroyed1) // false
    {
        if(newShipDestroyed2) // true
        {
            if (!newShipDestroyed3) // false
            {
                cout << "Update Fleet Status passed!" << endl;
            }
            else
            {
                cout << "Update Fleet Status failed. Detected false change" << endl;
            }
        }
        else
        {
            cout << "Update Fleet Status failed. Failed to detect ship sinking" << endl;
        }
    }
    else
    {
        cout << "Update Fleet Status failed. Detected sunk ship at start" << endl;
    }
}

void Tests::testIsWinner(void)
{
    Board b(sf::Color::Red);

    // Mock set-up of ship placement
    b.getTileNum(1,1).setTileOccupation(CARRIER);
    b.getTileNum(1,2).setTileOccupation(BATTLESHIP);
    b.getTileNum(1,3).setTileOccupation(CRUISER);
    b.getTileNum(1,4).setTileOccupation(SUBMARINE);
    b.getTileNum(1,5).setTileOccupation(DESTROYER);

    b.updateFleetStatus();

    bool test1 = b.isWinner(); // Should not detect winner - expect false

    // Simulate sinking all ships
    b.getTileNum(1,1).setTileOccupation(PREV_HIT);
    b.getTileNum(1,2).setTileOccupation(PREV_HIT);
    b.getTileNum(1,3).setTileOccupation(PREV_HIT);
    b.getTileNum(1,4).setTileOccupation(PREV_HIT);
    b.getTileNum(1,5).setTileOccupation(PREV_HIT);

    b.updateFleetStatus();

    bool test2 = b.isWinner(); // no ships remaining, so should be winner - expect true

    if (!test1) // false
    {
        if (test2) // true
        {
            cout << "Test Winner passed" << endl;
        }
        else
        {
            cout << "Test Winner failed. Failed to detect winner" << endl;
        }
    }
    else
    {
        cout << "Test Is Winner failed. Detected false winner" << endl;
    }
}

void Tests::testAnimationResetFrame(void)
{
     sf::Texture testTexture;
    
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

    Animation explosionAnimation(testTexture);

    explosionAnimation.changeFrame();
    explosionAnimation.changeFrame();
    explosionAnimation.changeFrame();

    explosionAnimation.resetFrame();

    if (explosionAnimation.getCurFrame() == 0)
    {
        cout << "Test Animation Reset Frame passed!" << endl;
    }
    else
    {
        cout << "Test Animation Reset Frame failed." << endl;
    }
}

void Tests::testAnimationDisplay(void)
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "Ultimate Battleship");

	
    // Load Texture from File
	sf::Texture test = sf::Texture{};
	try {
		test.loadFromFile("SplashAnimation.png");
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
    
    cout << "If splash animation displayed, Test Animation Display passed." << endl;
}

void Tests::testShipPlacement(void)
{
    Board b(sf::Color::Red);

    bool orientation = VERTICAL;
    int curShip = CARRIER;
    int shipLength = 5;
    bool isPlayer1 = true;
    bool isShipPlacement = true;


    // Should place ship vertically in upper left
    placeShip(b, curShip, shipLength, orientation, isPlayer1, isShipPlacement);

    // note that tile num is in (y,x) format (should be changed in future)
    if (b.getTileNum(4,0).getOccupationType() == CARRIER)
    {
        cout << "Test place ship passed!" << endl;
    }
    else
    {
        cout << "Test place ship failed." << endl;
    }
}