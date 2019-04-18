#include <SFML/Graphics.hpp>
namespace GUI {
using namespace sf;
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
  virtual void OnExit(const Event& event) {}
  Hoverable(Window& window) : window_{window} {}
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
}  // namespace GUI