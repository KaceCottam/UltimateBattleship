#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <memory>

using namespace sf;
using namespace fmt;
using namespace spdlog;
using namespace fmt::literals;

namespace GUI {
class Button : public Drawable {
 public:
  Button(const Transform &area, const Sprite &activated, const Sprite &disabled,
         const Sprite &selected, RenderWindow *window)
      : area_{area},
        activated_{activated},
        disabled_{disabled},
        selected_{selected},
        window_{window},
        current_sprite_{&activated_} {}
  void draw(RenderTarget &window,
            RenderStates states = RenderStates::Default) const override {
    if (states.transform == RenderStates::Default.transform)
      states.transform = area_;
    window.draw(*current_sprite_, states);
  }
  void ParseEvent(Event &event) {
    if (event.type == Event::MouseButtonPressed) {
      if (event.mouseButton.x >= area_.left &&
          event.mouseButton.x <= area_.width - area_.left &&
          event.mouseButton.y >= area_.top &&
          event.mouseButton.y <= area_.height - area_.top) {
        // info("Button clicked!");
        this->OnClick();
      }
    }
  }

 protected:
  virtual void OnClick() = 0;
  sf::Transform area_;
  sf::Sprite activated_;
  sf::Sprite disabled_;
  sf::Sprite selected_;
  sf::RenderWindow *window_;
  sf::Sprite *current_sprite_;
};
}  // namespace GUI

class ChangeColorBtn : public GUI::Button {
 public:
  ChangeColorBtn(const Transform &area, const Sprite &activated,
                 const Sprite &disabled, const Sprite &selected,
                 RenderWindow *window)
      : Button{area, activated, disabled, selected, window} {}

 private:
  std::size_t increment_;
  void OnClick() override {
    current_sprite_ = ((&activated_) + increment_++ % 3);
  }
};

int main() {
  RenderWindow window(VideoMode{800, 800}, "Button Test");
  Texture red{};
  Texture blue{};
  Texture green{};
  if (!red.loadFromFile("red.jpeg")) info("red not loaded");
  if (!blue.loadFromFile("blue.jpeg")) info("blue not loaded");
  if (!green.loadFromFile("bunny.jpeg")) info("green not loaded");
  std::cout << "test" << '\n';
  ChangeColorBtn button1{
      Transform(FloatRect{100, 100, 300, 200}), Sprite{red}, Sprite{blue}, Sprite{green}, &window};
  while (window.isOpen()) {
    Event event{};
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed) {
        window.close();
      }

      button1.ParseEvent(event);
    }

    window.clear();
    window.draw(button1);
    window.display();
  }
  return EXIT_SUCCESS;
}