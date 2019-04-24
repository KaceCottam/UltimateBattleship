#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"
#include "FiringMechanism.hpp"
#include "ShipPlacement.hpp"
#include "TileMovement.hpp"
#include "Animation.h"
#include "State.hpp"
#include <iostream>

using std::cout;
using std::endl;

bool upPressed = false, rightPressed = false, downPressed = false,
     leftPressed = false, rPressed = false, enterPressed = false;
bool isPlayer1 = true;

class Information : public State {
  public:
  bool LoadResources() override {
    if (!font.loadFromFile("ARIAL.TTF")) return false;
    text.setFont(font);
    text.setString(
        " WELCOME TO BATTLESHIP \n"
        "Rules:\n"
        "1. This is a two player game.\n"
        "2. You are Player1 and the computer is Player2.\n"
        "3. Each of you have a 10x10 board and 5 ships of various lengths.\n"
        "4. You can either place your ships manually or have it done "
        "randomly.\n"
        "5. Once all ships are placed, players take turns guessing where the "
        "other player's ships are.\n"
        "6. If you guessed correctly, you get a hit, if you didn't, you get a "
        "miss.\n"
        "7. A ship sinks when all of its cells have been hit.\n"
        "8. Guessing continues until one player sinks all ships of the other "
        "player, therefore winning.\n"
        "Use the arrow keys to move on the grid.\n"
        "Use 'r' to rotate the ship while placing it.\n"
        "Press enter to finish your turn.\n"
        "Press enter to continue");
    text.setCharacterSize(12U);
    return true;
  }
  void HandleEvent(const sf::Event &e) override {
    if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Enter) {
      enter_pressed_ = true;
    }
  }
  void draw(
      sf::RenderTarget &target,
      sf::RenderStates states = sf::RenderStates::Default) const override {
        target.draw(text);
  }
  std::optional<int> getNextState() const override {
    if(enter_pressed_) return 1;
    return {};
  }
  private:
  bool enter_pressed_{false};
  sf::Font font{};
  sf::Text text{};
};

class Placement : public State {
 public:
  Placement(Board *boards) : playBoard{boards} {}
  bool LoadResources() override {
    std::cout << "Placing" << std::endl;
    return true;
  }
  void HandleEvent(const sf::Event &event) override {
    if (isShipPlacement) {
      numHighlight(playBoard[isPlayer1], upPressed, downPressed, rightPressed,
                   leftPressed, rPressed, curOrientation, curShipLength);

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        enterPressed = true;
      } else {
        if (enterPressed == true) {
          placeShip(playBoard[isPlayer1], curShip, curShipLength,
                    curOrientation, isPlayer1, isShipPlacement);
          enterPressed = false;
        }
      }
    }
  }

  void draw(
      sf::RenderTarget &target,
      sf::RenderStates states = sf::RenderStates::Default) const override {
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
        target.draw(playBoard[isPlayer1].getTileNum(i, j));
      }
    }
  }

  std::optional<int> getNextState() const override {
    if (isShipPlacement) return {};
    return 2;
  }

 private:
  Board *playBoard;
  bool isShipPlacement = true;
  int curShip = CARRIER;
  int curShipLength = 5;
  int curOrientation = HORIZONTAL;
};

class Battle : public State {
 public:
  Battle(Board *boards, RenderWindow &window) : playBoard{boards}, window{window} {}
  bool LoadResources() override {
    std::cout << "Battling" << std::endl;
    try {
      splashTexture.loadFromFile("SplashAnimation.png");
    } catch (const std::exception &e) {
      std::cerr << e.what();
      return false;
    } catch (...) {
      std::cerr << "unexpected error";
      return false;
    }

    try {
      explosionTexture.loadFromFile("ExplosionAnimation.png");
    } catch (const std::exception &e) {
      std::cerr << e.what();
      return false;
    } catch (...) {
      return false;
      std::cerr << "unexpected error";
    }

    splashAnimation = Animation(splashTexture);
    explosionAnimation = Animation(explosionTexture);

    splashAnimation.scale(sf::Vector2f(5, 5));
    explosionAnimation.scale(sf::Vector2f(5, 5));
    return true;
  }

  void HandleEvent(const sf::Event &event) override {
    if (!isWinner)  // GAMEPLAY
    {
      bool waitingEnter = false;
      int fireStatus = INVALID;

      if (firstTurn) firstTurn = false;
      singleHighlight(playBoard[isPlayer1], upPressed, downPressed,
                      rightPressed, leftPressed);
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        enterPressed = true;
      } else {
        if (enterPressed == true) {
          if (!waitingEnter) {
            fireStatus = fire(playBoard[isPlayer1]);
            if (fireStatus != INVALID) {
              waitingEnter = true;
              auto placement_rect =
                  playBoard[isPlayer1]
                      .getTileNum(playBoard[isPlayer1].getCurYPos(),
                                  playBoard[isPlayer1].getCurXPos())
                      .getGlobalBounds();

              sf::Transform animationTransform;
              animationTransform.translate(
                  {placement_rect.left - 20, placement_rect.top - 20});
              if (fireStatus == HIT) {
                while (explosionAnimation.getCurFrame() < 9) {
                  if (gameClock.getElapsedTime().asSeconds() > .2) {
                    explosionAnimation.changeFrame();
                    gameClock.restart();
                  }

                  window.draw(explosionAnimation, animationTransform);
                  window.display();
                }
                explosionAnimation.resetFrame();
                bool newShipSunk = playBoard[isPlayer1].updateFleetStatus();
                if (newShipSunk) {
                  isWinner = playBoard[isPlayer1].isWinner();
                }
              } else {
                while (splashAnimation.getCurFrame() < 9) {
                  if (gameClock.getElapsedTime().asSeconds() > .2) {
                    splashAnimation.changeFrame();
                    gameClock.restart();
                  }
                  window.draw(splashAnimation, animationTransform);
                  window.display();
                }
                splashAnimation.resetFrame();
              }
              if (isPlayer1) {
                isPlayer1 = false;
              } else {
                isPlayer1 = true;
              }
            }
          } else {
            waitingEnter = false;
            isPlayer1 = false;
          }
          enterPressed = false;
        }
      }

    } else {
      if (isWinner) {
        cout << "PLAYER " << isPlayer1 + 1 << "WINS!" << endl;
      }
    }
  }

  void draw(
      sf::RenderTarget &target,
      sf::RenderStates states = sf::RenderStates::Default) const override {
    for (int i = 0; i < 10; ++i) {
      for (int j = 0; j < 10; ++j) {
        window.draw(playBoard[isPlayer1].getTileNum(i, j));
      }
    }
      if (firstTurn) {
        playBoard[0].resetHighlight();
        playBoard[0].resetFill();
        playBoard[1].resetHighlight();
        playBoard[1].resetFill();
      }
  }

  std::optional<int> getNextState() const override {
    if (!isWinner) return {};
    cout << "PLAYER " << isPlayer1 + 1 << " WINS!" << endl;
    return -1;
  }

 private:
  sf::Texture splashTexture{};
  sf::Texture explosionTexture{};
  Animation splashAnimation;
  Animation explosionAnimation;
  sf::Clock gameClock{};
  bool firstTurn = true;
  bool isWinner = false;
  Board *playBoard;
  sf::RenderWindow &window;
};

void SwitchStateIfNecessary(State *&current_state, sf::RenderWindow &window,
                            Board *playBoard) {
  auto next = current_state->getNextState();
  if (next.has_value()) {
    std::cout << "Switching state..." << std::endl;
    current_state->UnloadResources();
    delete current_state;
    switch (next.value()) {
      case 0:
        current_state = new Information();
        break;
      case 1:
        current_state = new Placement(playBoard);
        break;
      case 2:
        current_state = new Battle(playBoard,window);
        break;
      case -1:
        window.close();
        break;
    }
    current_state->LoadResources();
  }
}

int main() {
  sf::RenderWindow window(sf::VideoMode(500, 500), "Ultimate Battleship");

  State *current_state = new Information();
  current_state->LoadResources();
  Board playBoard[2] = {Board(sf::Color::Blue), Board(sf::Color::Red)};

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      current_state->HandleEvent(event);
    }

    SwitchStateIfNecessary(current_state,window,playBoard);

    window.clear();
    current_state->draw(window);
    window.display(); 
  }

  std::cin.get();
}