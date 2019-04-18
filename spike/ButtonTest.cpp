/*
 * This is an example of a button implemented in SFML
 * Things learned: Buttons are hard, 
 *                 textures must be loaded for sprites to work.
 * ClickyRoundButton is my implementation of the base button.
 * GUI::Button uses the GUI::Clickable and GUI::Hoverable interface.
 * 
 * In the program, a normally-white-but-colorized button can be found.
 * You click this button to make it change to the next color {red,blue,green}
 * It logs to the console when you hover, enter, exit, and click.
 * It also logs if the button texture is not correctly loaded.
 */
#include <array>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include "GUI/Button.hpp"
#include "SFMLUtil/FileNotFoundException.hpp"

using namespace sf;
using namespace fmt;
using namespace spdlog;
using namespace fmt::literals;

template<unsigned long long int Number>
class ClickyRoundButton : public GUI::Button {
 public:
  ClickyRoundButton(RenderWindow &window, const std::array<Sprite, Number>& buttons) 
  : Button{window}, buttons_{buttons} {
    SetSprite(&buttons_[increment++ % Number]);
  }

  void ParseEvent(const Event &event) {
    ParseMouseClick(event);
    ParseMouseHover(event);
  }

  void OnClick(const Event &event) override {
    SetSprite(&buttons_[increment++ % Number]);
    info("Clicked!");
  }

  void OnEnter(const Event &event) override {
    info("Enter button!");
  }

  void OnExit(const Event &event) override {
    info("Exit button!");
  }

  void OnHover(const Event &event) override {
    static std::size_t increment{0};
    if(!(increment++ % 64))
    {
      info("Hovering!");
    }
  }

 private:
  std::array<Sprite, Number> buttons_;
  std::size_t increment{0U};
};

int main() {
  RenderWindow window(VideoMode{800, 800}, "Button Test");
  Texture button_tex;
  if(!button_tex.loadFromFile("RoundButton1.png")) 
    throw FileNotFoundException("RoundButton1.png");
  Sprite button1{button_tex};
  Sprite button2{button_tex};
  Sprite button3{button_tex};
  button1.setColor(sf::Color::Red);
  button1.scale({3, 3});
  button2.setColor(sf::Color( 64, 64,255));
  button2.scale({3, 3});
  button3.setColor(sf::Color::Yellow);
  button3.scale({3, 3});

  ClickyRoundButton<3> button{window,{button1,button2,button3}};

  while (window.isOpen()) {
    Event event{};
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }
      button.ParseEvent(event);
    }

    window.clear();
    window.draw(button);
    window.display();
  }
  return EXIT_SUCCESS;
}