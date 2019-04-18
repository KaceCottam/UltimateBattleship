#include <SFML/Graphics.hpp>
namespace GUI {
using namespace sf;
class Clickable {
protected:
  void ParseMouseClick(const Event& event) {
    if (event.type == Event::MouseButtonPressed &&
        InArea({(float)event.mouseMove.x, (float)event.mouseMove.y})) {
      OnClick(event);
    }
  }
  virtual void OnClick(const Event& event) = 0;
  Clickable(Window& window) : window_{window} {}

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
}  // namespace GUI