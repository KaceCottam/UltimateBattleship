#pragma once
#include <SFML/Graphics.hpp>
namespace GUI {
class Clickable {
protected:
  void ParseMouseClick(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        InArea({(float)event.mouseButton.x, (float)event.mouseButton.y})) {
      OnClick(event);
    }
  }
  virtual void OnClick(const sf::Event& event) = 0;
  Clickable(sf::RenderWindow& window) : window_{window} {}

  void SetArea(const sf::FloatRect& area) { area_ = area; }

 private:
  inline bool InArea(const sf::Vector2f& point) const {
    if (point.x >= area_.left && point.x <= area_.width + area_.left &&
        point.y >= area_.top && point.y <= area_.height + area_.top)
      return true;
    return false;
  }
  sf::FloatRect area_;
  sf::RenderWindow& window_;
};
}  // namespace GUI