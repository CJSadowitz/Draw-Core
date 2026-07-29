#include "Deck.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Cards are shuffling", "[shuffle]") {
  unsigned int seed = 1;

  size_t cardAmount = 5;
  game::Card* cards = (game::Card*) std::malloc(cardAmount * sizeof(game::Card));
  for (int i = 0; i < cardAmount; i++) {
    game::Card c{game::CardType::RED, static_cast<game::CardValue>(i)};
    cards[i] = c;
  }

  game::Deck deck(cards, cardAmount, seed);
  deck.ShuffleCards();

  game::Card* shuffledCards = (game::Card*) std::malloc(cardAmount * sizeof(game::Card));
  std::memcpy(shuffledCards, deck.GetDrawPile(), cardAmount * sizeof(game::Card));

  game::Card* test = (game::Card*) std::malloc(cardAmount * sizeof(game::Card));

  test[0] = game::Card{game::CardType::RED, static_cast<game::CardValue>(2)};
  test[1] = game::Card{game::CardType::RED, static_cast<game::CardValue>(4)};
  test[2] = game::Card{game::CardType::RED, static_cast<game::CardValue>(3)};
  test[3] = game::Card{game::CardType::RED, static_cast<game::CardValue>(1)};
  test[4] = game::Card{game::CardType::RED, static_cast<game::CardValue>(0)};

  for (int i = 0; i < cardAmount; i++) {
    REQUIRE(shuffledCards[i].value == test[i].value);
  }

  if (cards) {
    free(cards);
    cards = nullptr;
  }
  if (shuffledCards) {
    free(shuffledCards);
    shuffledCards = nullptr;
  }
}

