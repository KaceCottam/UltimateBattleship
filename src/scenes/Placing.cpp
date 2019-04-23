#include "Placing.hpp"
#include <spdlog/spdlog.h>

Placing::Placing(Board& red_board, Board& blue_board)
    : red_board{red_board}, blue_board{blue_board} {
  spdlog::info("Switched to state 'Placing'");
}

void Placing::HandleEvent(const sf::Event &e) {

}

void Placing::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(player1 ? blue_board : red_board);
}

std::optional<int> Placing::getNextState() const {
  if (done_filling_out) return 1;
  return {};
}