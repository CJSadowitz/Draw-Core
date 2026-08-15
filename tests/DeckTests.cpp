#include "Deck.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("[DrawCards]") {
  std::vector<game::Card> cards = std::vector<game::Card>();
  for (int i = 0; i < 4; i++) {
      game::Card card0{static_cast<game::CardType>(i), game::CardValue::ZERO};
      cards.emplace_back(card0);
      for (int j = 0; j < 2; j++) {
        for(int k = 1; k < 13; k++) {
          game::Card card1{static_cast<game::CardType>(i), static_cast<game::CardValue>(k)};
          cards.emplace_back(card1);
        }
      }
  }

  for (auto card : cards) {
    spdlog::info("[DeckTests] {}", card.Print());
  }

  game::Deck deck = game::Deck(cards);

  SECTION("No Cards") {
    auto drawnCards = deck.DrawCards(0);
    REQUIRE(!drawnCards);
  }

  SECTION("Single Card") {
    auto drawnCards = deck.DrawCards(1);
    REQUIRE(drawnCards);
    REQUIRE(drawnCards.value().size() == 1);
  }

  SECTION("Two Cards") {

  }

  SECTION("Four Cards") {

  }

  SECTION("Until Playable") {

  }
}
