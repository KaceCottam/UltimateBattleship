#include <SFML/Graphics.hpp>

#include "GUI/Button.hpp"
#include "GUI/GameEngine.hpp"
#include "GUI/Scene.hpp"

#include "SFMLUtil/FileNotFoundException.hpp"

using namespace sf;
using namespace GUI;
using namespace fmt;
using namespace spdlog;

class ExitButton : public GUI::Button {
 public:
  ExitButton(RenderWindow &window, Sprite *sprite) : Button{window} {
    SetSprite(sprite);
  }

  void OnClick(const Event &event) override { info("Clicked!"); }

  void OnEnter(const Event &event) override { info("Enter button!"); }

  void OnExit(const Event &event) override { info("Exit button!"); }
};

class MainMenu : public GUI::Scene {
 public:
  explicit MainMenu(RenderWindow &window) : Scene(window) {}
  void draw(RenderTarget &target,
            RenderStates states = RenderStates::Default) const override {
    target.draw(*main_menu_text);
    target.draw(*button);
  }
  void UnloadResources() override {}
  void LoadResources() override {
    info("Loading font");
    regular_font = std::make_unique<Font>();
    if (!regular_font->loadFromFile("ARIAL.TFF")) {
      throw SFMLUtil::FileNotFoundException("ARIAL.TFF");
    }
    info("Loading text");
    main_menu_text =
        std::make_unique<Text>("Welcome to the menu!", *regular_font, 18);
    info("Loading textures");
    button_texture = std::make_unique<Texture>();
    if (!button_texture->loadFromFile("RoundButton1.png")) {
      throw SFMLUtil::FileNotFoundException("RoundButton1.png");
    }
    info("Loading sprites");
    button_sprite = std::make_unique<Sprite>(*button_texture);
    button_sprite->setOrigin(button_sprite->getLocalBounds().width / 2,
                             button_sprite->getLocalBounds().height / 2);
    button_sprite->setPosition(300, 300);
    button_sprite->setColor(Color::Red);
    info("Loading interactables");
    button = std::make_unique<ExitButton>((RenderWindow &)window_,
                                          &(*button_sprite));
  }
  void HandleEvent(const Event &event) override { button->ParseEvent(event); }

 private:
  std::unique_ptr<Font> regular_font;
  std::unique_ptr<Text> main_menu_text;
  std::unique_ptr<Texture> button_texture;
  std::unique_ptr<Sprite> button_sprite;
  std::unique_ptr<ExitButton> button;
};

int main() {
  RenderWindow window{VideoMode{600, 600}, "Scene Manager Test"};
  GUI::Game game{window};
  MainMenu main_menu{window};
  game.AddScene(&main_menu);
  game.Play();
}