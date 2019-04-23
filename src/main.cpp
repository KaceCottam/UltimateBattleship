#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include <GUI/GameEngine.hpp>

#include "scenes/mainmenu.hpp"
#include "scenes/placeships.hpp"
#include "scenes/attackships.hpp"

int main(int argc, char** argv) {
  sf::RenderWindow window{sf::VideoMode{800,600},"Ultimate Battleship"};
  GUI::Game gameEngine{window};
  MainMenu mainMenu{window};
  gameEngine.AddScene(&mainMenu);
  gameEngine.Play();

  std::cin.get();
}