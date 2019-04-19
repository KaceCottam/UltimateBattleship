#pragma once
#include <SFML/Graphics.hpp>
namespace GUI {
class Hoverable {
 protected:
  void ParseMouseHover(const sf::Event& event) {
    static bool in_area_prev{in_area_};
    if (event.type == sf::Event::MouseMoved &&
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
  virtual void OnHover(const sf::Event& event) {}
  virtual void OnEnter(const sf::Event& event) {}
  virtual void OnExit(const sf::Event& event) {}
  Hoverable(sf::RenderWindow& window) : window_{window} {}
  void SetArea(const sf::FloatRect& area) { area_ = area; }

 private:
  inline bool InArea(const sf::Vector2f& point) {
    if (point.x >= area_.left && point.x <= area_.width + area_.left &&
        point.y >= area_.top && point.y <= area_.height + area_.top) {
      in_area_ = true;
    } else {
      in_area_ = false;
    }
    return in_area_;
  }

  bool in_area_;
  sf::FloatRect area_;
  sf::RenderWindow& window_;
};
}  // namespace GUI