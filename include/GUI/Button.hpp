#pragma once
#include <SFML/Graphics.hpp>
#include "Clickable.hpp"
#include "Hoverable.hpp"

namespace GUI {
class Button : public Clickable, public Hoverable, public sf::Drawable {
 public:
  Button(sf::RenderWindow &window)
      : Clickable{window}, Hoverable{window}, current_sprite_{nullptr} {}

  void SetSprite(sf::Sprite *sprite) {
    current_sprite_ = sprite;
    SetArea(current_sprite_->getGlobalBounds());
  }

  void draw(sf::RenderTarget &window,
            sf::RenderStates states = sf::RenderStates::Default) const override {
    window.draw(*current_sprite_, states);
  }

  virtual void ParseEvent(const sf::Event &event){
    ParseMouseClick(event);
    ParseMouseHover(event);
  }

 private:
  void SetArea(const sf::FloatRect &area) {
    Clickable::SetArea(area);
    Hoverable::SetArea(area);
  }
  sf::Sprite *current_sprite_;
};
}  // namespace GUI