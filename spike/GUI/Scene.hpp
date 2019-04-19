#pragma once
#include <SFML/Graphics.hpp>

namespace GUI {
class Scene : public sf::Drawable {
 public:
  Scene(sf::RenderTarget &window) : window_{window} {}
  virtual void LoadResources() = 0;
  virtual void UnloadResources() = 0;
  virtual void HandleEvent(const sf::Event &event) = 0;
  virtual ~Scene() {};

 protected:
  sf::RenderTarget &window_;
};
}  // namespace GUI