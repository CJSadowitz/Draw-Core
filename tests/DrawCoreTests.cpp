#include "DrawCore.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Dealing small deck to small playerCount", "[dealCards]") {
  unsigned int seed = 1;
  size_t playerCount = 2;

  game::DrawCore game = game::DrawCore(seed, playerCount);
  REQUIRE(!game.DealCards(20));

  unsigned int cardAmount = 12;
}

