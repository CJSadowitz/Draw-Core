#include "Deck.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Cards are shuffling", "[shuffle]") {
  unsigned int seed = 1;

  size_t cardAmount = 5;
  auto cards = std::vector<game::Card>();
  for (int i = 0; i < cardAmount; i++) {
    game::Card c{game::CardType::RED, static_cast<game::CardValue>(i)};
    cards.emplace_back(c);
  }

  game::Deck deck(cards, seed);
  deck.ShuffleCards();

  auto shuffledCards = deck.GetDrawPile();

  auto test = std::vector<game::Card>();

  test.emplace_back(game::Card{game::CardType::RED, static_cast<game::CardValue>(2)});
  test.emplace_back(game::Card{game::CardType::RED, static_cast<game::CardValue>(3)});
  test.emplace_back(game::Card{game::CardType::RED, static_cast<game::CardValue>(4)});
  test.emplace_back(game::Card{game::CardType::RED, static_cast<game::CardValue>(1)});
  test.emplace_back(game::Card{game::CardType::RED, static_cast<game::CardValue>(0)});

  for (int i = 0; i < cardAmount; i++) {
    REQUIRE(shuffledCards[i].value == test[i].value);
  }
}

