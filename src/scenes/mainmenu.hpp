#pragma once
#include <GUI/Button.hpp>
#include <GUI/Scene.hpp>
#include <SFMLUtil/FileNotFoundException.hpp>

class MenuButton : public GUI::Button {
 public:
  MenuButton(sf::RenderWindow &window) : Button(window) {}
  void OnClick(const sf::Event &event) override { value_ = true; }
  void OnEnter(const sf::Event &event) override { Button::SetSprite(hovering_); }
  void OnExit(const sf::Event &event) override { Button::SetSprite(not_hovering_); }

  void SetSprite(bool hovering, sf::Sprite *&spr) {
    if (hovering)
      hovering_ = spr;
    else
      not_hovering_ = spr;
  }

  bool value_{false};

 private:
  sf::Sprite *hovering_;
  sf::Sprite *not_hovering_;
};

class MainMenu : public GUI::Scene {
 public:
  MainMenu(sf::RenderWindow &window) : Scene{window} {}
  SceneId HandleEvent(const sf::Event &event) override {
    // ! If we change the order that the scenes are added in, this must change
    // ! too.
    constexpr SceneId current = 0;
    constexpr SceneId play = 2;
    constexpr SceneId help = 1;
    constexpr SceneId exit = 0;  // TODO: Change to number of scenes

    play_button_->ParseEvent(event);
    exit_button_->ParseEvent(event);

    if (play_button_->value_) return play;
    if (exit_button_->value_) return exit;
    if (help_button_->value_) return help;
    return current;
  }
  void LoadResources() override {
    play_button_tex_ = new sf::Texture();
    if (!play_button_tex_->loadFromFile("assets/play_button.png"))
      throw SFMLUtil::FileNotFoundException("play_button.png");
    play_button_spr_hover_ = new sf::Sprite(*play_button_tex_);
    play_button_spr_hover_->setColor(sf::Color::Green);
    play_button_spr_hover_->setOrigin(
        play_button_spr_hover_->getLocalBounds().width / 2,
        play_button_spr_hover_->getLocalBounds().height / 2);
    play_button_spr_hover_->setPosition(window_.getSize().x / 2,
                                      window_.getSize().y / 2);
    play_button_spr_not_hover_ = new sf::Sprite(*play_button_tex_);
    play_button_spr_not_hover_->setColor(sf::Color::White);
    play_button_spr_not_hover_->setOrigin(
        play_button_spr_not_hover_->getLocalBounds().width / 2,
        play_button_spr_not_hover_->getLocalBounds().height / 2);
    play_button_spr_not_hover_->setPosition(window_.getSize().x / 2,
                                          window_.getSize().y / 2);

    play_button_ = new MenuButton(window_);
    play_button_->SetSprite(1, play_button_spr_hover_);
    play_button_->SetSprite(0, play_button_spr_not_hover_);

    help_button_tex_ = new sf::Texture();
    if (!help_button_tex_->loadFromFile("assets/help_button.png"))
      throw SFMLUtil::FileNotFoundException("help_button.png");
    help_button_spr_hover_ = new sf::Sprite(*help_button_tex_);
    help_button_spr_hover_->setColor(sf::Color::Red);
    help_button_spr_hover_->setOrigin(
        help_button_spr_hover_->getLocalBounds().width / 2,
        help_button_spr_hover_->getLocalBounds().height / 2);
    help_button_spr_hover_->setPosition(window_.getSize().x / 2,
                                      window_.getSize().y / 2);
    help_button_spr_not_hover_ = new sf::Sprite(*help_button_tex_);
    help_button_spr_not_hover_->setColor(sf::Color::White);
    help_button_spr_not_hover_->setOrigin(
        help_button_spr_not_hover_->getLocalBounds().width / 2,
        help_button_spr_not_hover_->getLocalBounds().height / 2);
    help_button_spr_not_hover_->setPosition(window_.getSize().x / 2,
                                          window_.getSize().y / 2 + 200);

    help_button_ = new MenuButton(window_);
    help_button_->SetSprite(1, help_button_spr_hover_);
    help_button_->SetSprite(0, help_button_spr_not_hover_);

    exit_button_tex_ = new sf::Texture();
    if (!exit_button_tex_->loadFromFile("assets/exit_button.png"))
      throw SFMLUtil::FileNotFoundException("exit_button.png");
    exit_button_spr_hover_ = new sf::Sprite(*exit_button_tex_);
    exit_button_spr_hover_->setColor(sf::Color::Red);
    exit_button_spr_hover_->setOrigin(
        exit_button_spr_hover_->getLocalBounds().width / 2,
        exit_button_spr_hover_->getLocalBounds().height / 2);
    exit_button_spr_hover_->setPosition(window_.getSize().x / 2,
                                      window_.getSize().y / 2);
    exit_button_spr_not_hover_ = new sf::Sprite(*exit_button_tex_);
    exit_button_spr_not_hover_->setColor(sf::Color::White);
    exit_button_spr_not_hover_->setOrigin(
        exit_button_spr_not_hover_->getLocalBounds().width / 2,
        exit_button_spr_not_hover_->getLocalBounds().height / 2);
    exit_button_spr_not_hover_->setPosition(window_.getSize().x / 2,
                                          window_.getSize().y / 2 + 400);

    exit_button_ = new MenuButton(window_);
    exit_button_->SetSprite(1, exit_button_spr_hover_);
    exit_button_->SetSprite(0, exit_button_spr_not_hover_);

    background_texture_ = new sf::Texture();
    if (!background_texture_->loadFromFile("assets/mainmenu_background.png"))
      throw SFMLUtil::FileNotFoundException("mainmenu_background.png");
    background_ = new sf::Sprite(*background_texture_);
  }
  void UnloadResources() override {
    if(!background_) return;
    delete play_button_tex_;
    delete play_button_spr_hover_;
    delete play_button_spr_not_hover_;
    delete play_button_;

    delete help_button_tex_;
    delete help_button_spr_hover_;
    delete help_button_spr_not_hover_;
    delete help_button_;

    delete exit_button_tex_;
    delete exit_button_spr_hover_;
    delete exit_button_spr_not_hover_;
    delete exit_button_;

    delete background_texture_;
    delete background_;
  }
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    target.draw(*play_button_);
    target.draw(*exit_button_);
    target.draw(*background_);
  }

 private:
  // * These will all be on the heap.
  sf::Texture *play_button_tex_;
  sf::Sprite *play_button_spr_hover_;
  sf::Sprite *play_button_spr_not_hover_;
  MenuButton *play_button_;

  sf::Texture *help_button_tex_;
  sf::Sprite *help_button_spr_hover_;
  sf::Sprite *help_button_spr_not_hover_;
  MenuButton *help_button_;

  sf::Texture *exit_button_tex_;
  sf::Sprite *exit_button_spr_hover_;
  sf::Sprite *exit_button_spr_not_hover_;
  MenuButton *exit_button_;

  sf::Texture *background_texture_;
  sf::Sprite *background_;
};