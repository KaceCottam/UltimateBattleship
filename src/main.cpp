#include <iostream>
#include <memory>
#include <optional>

#include <SFML/Graphics.hpp>
#include <Board.h>

struct State {
 public:
  virtual void LoadResources() { }
  virtual void UnloadResources() { }
  virtual void operator()() = 0;
};

class Placing : public State {
  public:
  void operator()() override {

  }

  private:
  Board *boards[2];
};

int main(int argc, char** argv) {
  enum State {
    PLACE,
    BATTLE
  } current_state{PLACE};
  enum Player {
    RED,
    BLUE
  };
  sf::RenderWindow window(sf::VideoMode(800,600),"Ultimate Battleship");
  std::optional<Player> winner;
  Board red_board(sf::Color::Red);
  Board blue_board(sf::Color::Blue);

  while(window.isOpen()) {
    sf::Event e;
    while(window.pollEvent(e)) {
      if(e.type == sf::Event::Closed) window.close();

    }
  }

  std::cin.get();
}