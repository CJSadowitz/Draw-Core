#include "DrawCore.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Dealing small deck to small playerCount", "[dealCards]") {
  unsigned int seed = 1;
  size_t playerCount = 2;

  game::DrawCore game = game::DrawCore(seed, playerCount);
  REQUIRE(!game.DealCards(20));
}

TEST_CASE("Dealing full deck to 8 players", "[dealCards]") {
  unsigned int seed = 1;
  size_t playerCount = 8;
  auto cards = std::vector<game::Card>();
  for (int i = 0; i < 4; i++) {
      game::Card c{static_cast<game::CardType>(i), game::CardValue::ZERO};
      cards.emplace_back(c);
      for (int j = 0; j < 2; j++) {
        for(int k = 0; k < 13; k++) {
          c.value = static_cast<game::CardValue>(k);
          cards.emplace_back(c);
        }
      }
  }
  REQUIRE(cards.size() == 108);
  game::DrawCore game = game::DrawCore(seed, playerCount, cards);
  REQUIRE(game.DealCards(20));
}

