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
#include <stdexcept>
#include <fmt/format.h>
#include <spdlog/spdlog.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace fmt;
using namespace spdlog;
using namespace fmt::literals;

namespace GUI {
class Clickable {
 protected:
  void ParseMouseClick(const Event& event) {
    if (event.type == Event::MouseButtonPressed &&
        InArea({(float)event.mouseMove.x, (float)event.mouseMove.y})) {
      OnClick(event);
    }
  }
  virtual void OnClick(const Event& event) = 0;
  Clickable(Window& window)
      : window_{window} {}

  void SetArea(const FloatRect& area) { area_ = area; }

 private:
  inline bool InArea(const Vector2f& point) const {
    if (point.x >= area_.left && point.x <= area_.width + area_.left &&
        point.y >= area_.top && point.y <= area_.height + area_.top)
      return true;
    return false;
  }
  FloatRect area_;
  Window& window_;
};

class Hoverable {
 protected:
  void ParseMouseHover(const Event& event) {
    static bool in_area_prev{in_area_};
    if (event.type == Event::MouseMoved &&
        InArea({(float)event.mouseMove.x, (float)event.mouseMove.y})) {
      if (in_area_ != in_area_prev) {
        OnEnter(event);
      }
      OnHover(event);
    } else if (in_area_ != in_area_prev) {
      OnExit(event);
    }

    in_area_prev = in_area_;
  }
  virtual void OnHover(const Event& event) {}
  virtual void OnEnter(const Event& event) {}
  virtual void OnExit(const Event & event) {}
  Hoverable(Window& window)
      : window_{window} {}
  void SetArea(const FloatRect& area) { area_ = area; }

 private:
  inline bool InArea(const Vector2f& point) {
    if (point.x >= area_.left && point.x <= area_.width + area_.left &&
        point.y >= area_.top && point.y <= area_.height + area_.top) {
      in_area_ = true;
    } else {
      in_area_ = false;
    }
    return in_area_;
  }

  bool in_area_;
  FloatRect area_;
  Window& window_;
};

class Button : public Clickable, public Hoverable, public Drawable {
 public:
  Button(Window &window)
      : Clickable{window}, Hoverable{window}, current_sprite_{nullptr} { }

  void SetSprite(Sprite* sprite) {
    current_sprite_ = sprite;
    SetArea(current_sprite_->getGlobalBounds());
  }

  void draw(RenderTarget& window,
            RenderStates states = RenderStates::Default) const override {
    window.draw(*current_sprite_,states);
  }

 private:
  void SetArea(const FloatRect &area) {
    Clickable::SetArea(area);
    Hoverable::SetArea(area);
  }
  Sprite *current_sprite_;
};

struct FileNotFoundException : std::exception {
  FileNotFoundException(const char *fileName) {
    error(format("File \"{}\" not found!",fileName));
  }
};

}  // namespace GUI

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
    throw GUI::FileNotFoundException("RoundButton1.png");
  Sprite button1{button_tex};
  Sprite button2{button_tex};
  Sprite button3{button_tex};
  button1.setColor(sf::Color::Red);
  button1.scale({3, 3});
  button2.setColor(sf::Color( 64, 64,255));
  button2.scale({3, 3});
  button3.setColor(sf::Color::Green);
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