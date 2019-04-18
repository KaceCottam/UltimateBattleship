#include <SFML/Graphics.hpp>
#include "Clickable.hpp"
#include "Hoverable.hpp"

namespace GUI {
using namespace sf;
class Button : public Clickable, public Hoverable, public Drawable {
 public:
  Button(Window &window)
      : Clickable{window}, Hoverable{window}, current_sprite_{nullptr} {}

  void SetSprite(Sprite *sprite) {
    current_sprite_ = sprite;
    SetArea(current_sprite_->getGlobalBounds());
  }

  void draw(RenderTarget &window,
            RenderStates states = RenderStates::Default) const override {
    window.draw(*current_sprite_, states);
  }

 private:
  void SetArea(const FloatRect &area) {
    Clickable::SetArea(area);
    Hoverable::SetArea(area);
  }
  Sprite *current_sprite_;
};
}  // namespace GUI