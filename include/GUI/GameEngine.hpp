#pragma once
#include <map>

#include <SFML/Graphics.hpp>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include "Scene.hpp"
#include "../SFMLUtil/BadIndexError.hpp"

namespace GUI {
using namespace sf;
using namespace fmt;
using namespace spdlog;
class Game {
 public:
  using SceneId = std::size_t;

  Game(RenderWindow& window) : window_{window} {}

  void AddScene(Scene *scene) { scenes_[scenes_.size()] = scene; }

  bool Play() {
    LoadScene(current_id_);
    while (window_.isOpen()) {
      Event event;
      while (window_.pollEvent(event)) {
        if (event.type == Event::Closed) window_.close();

        auto result = scenes_[current_id_]->HandleEvent(event);
        try {
          if (result != current_id_) LoadScene(result);
        } catch(const SFMLUtil::BadIndexError &e) {
          warn("Disregard error if index == size!");
          if (result == scenes_.size()) window_.close();
          else throw e;
        }
      }

      window_.clear();
      window_.draw(*scenes_[current_id_]);
      window_.display();
    }
    UnloadScene();

    return EXIT_SUCCESS;
  }

 private:
  void LoadScene(const SceneId id) {
    try {
      scenes_.at(id)->LoadResources();
    } catch (const std::exception &e) {
      error(format("Scene ID {} does not exist!", id));
      throw SFMLUtil::BadIndexError(id, scenes_.size());
    } catch (...) {
      error("Unknown error occured while loading scene.");
    }
    UnloadScene();
    current_id_ = id;
  }

  void UnloadScene() { scenes_[current_id_]->UnloadResources(); }

  std::map<SceneId, Scene *> scenes_;

  SceneId current_id_;
  RenderWindow &window_;
};

}  // namespace GUI