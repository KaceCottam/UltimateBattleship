#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include "Board.h"

class State : public sf::Drawable {
 public:
  virtual void HandleEvent(const sf::Event &e) = 0;
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states = sf::RenderStates::Default) const = 0;
  virtual std::optional<int> getNextState() const = 0;
  virtual bool LoadResources() { return true; }
  virtual bool UnloadResources() { return true; }
};