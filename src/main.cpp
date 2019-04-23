#include <iostream>

#include <Board.h>
#include <SFML/Graphics.hpp>

#include "scenes/State.hpp"
#include "scenes/Placing.hpp"

void SwitchStateIfNecessary(State *&current_state, sf::RenderWindow &window,
                            Board &red_board, Board &blue_board) {
  if (current_state->getNextState().has_value()) {
    current_state->UnloadResources();
    delete current_state;
    switch (current_state->getNextState().value()) {
      case 0:
        current_state = new Placing(red_board, blue_board);
        break;
      case 1:
        // TODO: current_state = new Battling();
        break;
      case -1:
        window.close();
        break;
    }
    current_state->LoadResources();
  }
}

int main(int argc, char **argv) {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Ultimate Battleship");
  Board red_board(sf::Color::Red);
  Board blue_board(sf::Color::Blue);

  State *current_state = new Placing(red_board, blue_board);
  current_state->LoadResources();

  while (window.isOpen()) {
    { // wrapped in scope for event
      sf::Event e;
      while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) window.close();
        current_state->HandleEvent(e);
      }
    }

    SwitchStateIfNecessary(current_state, window, red_board, blue_board);

    window.clear();
    window.draw(*current_state);
    window.display();
  }

  std::cin.get();
}