#include <memory>
#include <SFML/Graphics.hpp>
#include <GUI/GameEngine.hpp>
#include "scenes/mainmenu.hpp"
#include "scenes/placeships.hpp"
#include "scenes/attackships.hpp"
int main(int argc, char** argv) {
  sf::RenderWindow window{sf::VideoMode{800,600},"Ultimate Battleship"};
  GUI::Game gameEngine{window};
  auto mainMenu = std::make_unique<MainMenu>(window);
  gameEngine.AddScene(mainMenu.get());
  gameEngine.Play();
}