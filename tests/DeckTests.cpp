#include "Deck.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("[DrawCards] [Deck]") {
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
  for (int i = 0; i < 4; i++) {
    cards.emplace_back(game::Card{game::CardType::WILD, game::CardValue::CHANGE_COLOR});
    cards.emplace_back(game::Card{game::CardType::WILD, game::CardValue::CHANGE_COLOR_PLUS_FOUR});
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
    REQUIRE(deck.GetCards().size() == 107);
  }

  SECTION("Plus Two Cards") {
    auto drawnCards = deck.DrawCards(2);
    REQUIRE(drawnCards);
    REQUIRE(drawnCards.value().size() == 2);
    REQUIRE(deck.GetCards().size() == 106);
  }

  SECTION("Plus Four Cards") {
    auto drawnCards = deck.DrawCards(4);
    REQUIRE(drawnCards);
    REQUIRE(drawnCards.value().size() == 4);
    REQUIRE(deck.GetCards().size() == 104);
  }
}

TEST_CASE("[PlayCard] [Deck]") {
  auto cards = std::vector<game::Card>();
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ONE});
  game::Deck deck = game::Deck(cards);
  SECTION("Playable") {
    auto triedCard = game::Card{game::CardType::RED, game::CardValue::ONE};
    auto card = deck.PlayCard(triedCard);
    REQUIRE(card);
    REQUIRE(card.value() == triedCard);
  }
  SECTION("Not Playable") {
    auto card = deck.PlayCard(game::Card{game::CardType::GREEN, game::CardValue::ZERO});
    REQUIRE(!card);
  }
  SECTION("No Cards to Play") {
    auto emptyDeck = game::Deck(std::vector<game::Card>());
    auto card = emptyDeck.PlayCard(game::Card{game::CardType::GREEN, game::CardValue::ZERO});
    REQUIRE(!card);
  }
}

TEST_CASE("[AddCards] [Deck]") {
  game::Deck deck = game::Deck(std::vector<game::Card>());
  SECTION("Single") {
    auto card = game::Card{game::CardType::RED, game::CardValue::ZERO};
    auto cards = std::vector<game::Card>();
    cards.emplace_back(card);
    deck.AddCards(cards);
    REQUIRE(deck.GetCards().size() == 1);
  }
  SECTION("Multiple") {
    auto c1 = game::Card{game::CardType::RED, game::CardValue::ZERO};
    auto c2 = game::Card{game::CardType::RED, game::CardValue::ONE};
    auto cards = std::vector<game::Card>();
    cards.emplace_back(c1);
    cards.emplace_back(c2);
    deck.AddCards(cards);
    REQUIRE(deck.GetCards().size() == 2);
  }
  SECTION("None") {
    deck.AddCards(std::vector<game::Card>());
    REQUIRE(deck.GetCards().size() == 0);
  }
}

TEST_CASE("[HasCard] [Deck]") {
  auto card = game::Card{game::CardType::RED, game::CardValue::ZERO};
  auto cards = std::vector<game::Card>();
  cards.emplace_back(card);
  game::Deck deck = game::Deck(cards);
  SECTION("Actually has the card") {
    REQUIRE(deck.HasCard(card));
  }
  SECTION("Doesn't have the card") {
    REQUIRE(!deck.HasCard(game::Card{game::CardType::GREEN, game::CardValue::ZERO}));
  }
  SECTION("Deck has no cards") {
    auto emptyDeck = game::Deck(std::vector<game::Card>());
    REQUIRE(!emptyDeck.HasCard(card));
  }
}
