#pragma once
#include "State.hpp"
class Placing : public State {
 public:
  Placing(Board &red_board, Board &blue_board);
  void HandleEvent(const sf::Event &e) override;
  void draw(sf::RenderTarget &target,
            sf::RenderStates states = sf::RenderStates::Default) const override;
  std::optional<int> getNextState() const override;

 private:
  bool player1{false};
  Board &red_board;
  Board &blue_board;
  bool done_filling_out{false};
};