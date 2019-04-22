#pragma once
#include <SFML/Graphics.hpp>

namespace GUI {
class Scene : public sf::Drawable {
 public:
  using SceneId = std::size_t;

  Scene(sf::RenderTarget &window) : window_{window} {}
  virtual void LoadResources() = 0;
  virtual void UnloadResources() = 0;
  virtual SceneId HandleEvent(const sf::Event &event) = 0;
  virtual ~Scene() {};

 protected:
  sf::RenderTarget &window_;
};
}  // namespace GUI