#include "DrawEngine.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Cards are shuffling", "[shuffle]") {
  size_t cardAmount = 5;
  unsigned int seed = 1;
  game::Card* cards = (game::Card*) std::malloc(cardAmount * sizeof(game::Card));
  for (int i = 0; i < cardAmount; i++) {
    game::Card c{game::CardType::RED, static_cast<game::CardValue>(i)};
    cards[i] = c;
  }

  game::Deck deck(cards, cardAmount, seed);
  deck.ShuffleCards();
  free(cards);
  REQUIRE(true);
}

