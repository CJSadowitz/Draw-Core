#include "Card.hpp"
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

TEST_CASE("Shuffling empty deck", "[shuffle]") {
  unsigned int seed = 1;
  game::Deck deck(std::vector<game::Card>(), seed);
  deck.ShuffleCards();
  REQUIRE(deck.GetDrawPile().size() == 0);
}

TEST_CASE("Resetting discard pile", "[resetDiscard]") {
  unsigned int seed = 1;
  size_t cardAmount = 10;
  auto cards = std::vector<game::Card>();
  for (int i = 0; i < cardAmount; i++) {
    game::Card c{game::CardType::RED, static_cast<game::CardValue>(i)};
    cards.emplace_back(c);
  }

  game::Deck deck(cards, seed);
  deck.ShuffleCards();

  REQUIRE(deck.ResetDiscardPile());
  REQUIRE(deck.GetDiscardPile().size() == 1);
  REQUIRE(deck.GetDrawPile().size() == 9);
  REQUIRE(!deck.ResetDiscardPile());
}

TEST_CASE("Resetting empty deck", "[resetDiscard]") {
  unsigned int seed = 1;
  auto cards = std::vector<game::Card>();
  game::Deck deck(cards, seed);
  deck.ShuffleCards();
  REQUIRE(!deck.ResetDiscardPile());
}

TEST_CASE("Draw cards from empty deck", "[drawCards]") {
  unsigned int seed = 1;
  auto cards = std::vector<game::Card>();
  game::Deck deck(cards, seed);
  REQUIRE(!deck.DrawCards());
}

TEST_CASE("Draw card same type", "[drawCards]") {
  unsigned int seed = 1;
  size_t cardAmount = 2;
  auto cards = std::vector<game::Card>();
  for (int i = 0; i < cardAmount; i++) {
    game::Card c{game::CardType::RED, static_cast<game::CardValue>(i)};
    cards.emplace_back(c);
  }
  game::Deck deck(cards, seed);
  REQUIRE(deck.ResetDiscardPile());
  auto drawnCards = deck.DrawCards();
  REQUIRE(drawnCards);
  REQUIRE(drawnCards.value()[0].value == game::CardValue::ZERO);
}

TEST_CASE("Draw card same value", "[drawCards]") {
  unsigned int seed = 1;
  auto cards = std::vector<game::Card>();
  game::Card c1{game::CardType::RED, game::CardValue::TWO};
  cards.emplace_back(c1);
  game::Card c2{game::CardType::GREEN, game::CardValue::TWO};
  cards.emplace_back(c2);
  game::Deck deck(cards, seed);
  REQUIRE(deck.ResetDiscardPile());
  auto drawnCards = deck.DrawCards();
  REQUIRE(drawnCards);
  REQUIRE(drawnCards.value()[0].type == game::CardType::RED);
}

TEST_CASE("Draw card wild", "[drawCards]") {
  // Nothing stops type and value overlapping in undesired way...
  unsigned int seed = 1;
  auto cards = std::vector<game::Card>();
  game::Card c1{game::CardType::WILD, game::CardValue::ZERO};
  cards.emplace_back(c1);
  game::Card c2{game::CardType::RED, game::CardValue::CHANGE_COLOR};
  cards.emplace_back(c2);
  game::Deck deck(cards, seed);
  REQUIRE(deck.ResetDiscardPile());
  auto drawnCards = deck.DrawCards();
  REQUIRE(drawnCards);
  REQUIRE(drawnCards.value()[0].type == game::CardType::WILD);
}

TEST_CASE("No valid drawable card", "[drawCards]") {
  unsigned int seed = 1;
  auto cards = std::vector<game::Card>();
  game::Card c1{game::CardType::RED,    game::CardValue::ZERO};
  game::Card c2{game::CardType::GREEN,  game::CardValue::ONE};
  game::Card c3{game::CardType::BLUE,   game::CardValue::TWO};
  game::Card c4{game::CardType::YELLOW, game::CardValue::THREE};
  cards.emplace_back(c1);
  cards.emplace_back(c2);
  cards.emplace_back(c3);
  cards.emplace_back(c4);
  game::Deck deck(cards, seed);
  REQUIRE(deck.ResetDiscardPile());
  auto drawnCards = deck.DrawCards();
  REQUIRE(!drawnCards);
}

TEST_CASE("Draw a lot of cards", "[drawCards]") {
  unsigned int seed = 1;
  size_t cardAmount = 5;
  size_t typeAmount = 3;
  auto cards = std::vector<game::Card>();
  for (int i = 0; i < cardAmount; i++) {
    for (int j = 0; j < typeAmount; j++) {
      game::Card c{static_cast<game::CardType>(j), static_cast<game::CardValue>(i)};
      cards.emplace_back(c);
    }
  }
  game::Deck deck(cards, seed);
  REQUIRE(deck.ResetDiscardPile());
  deck.ShuffleCards();
  REQUIRE(deck.DrawCards());
}

TEST_CASE("Add no cards to an empty deck", "[addCards]") {
  unsigned int seed = 1;
  auto cards = std::vector<game::Card>();
  game::Deck deck(cards, seed);
  REQUIRE(!deck.AddCards(cards));
}

TEST_CASE("Add no cards to a deck", "[addCards]") {
  unsigned int seed = 1;
  size_t cardAmount = 2;
  auto cards = std::vector<game::Card>();
  for (int i = 0; i < cardAmount; i++) {
    game::Card c{game::CardType::RED, static_cast<game::CardValue>(i)};
    cards.emplace_back(c);
  }
  game::Deck deck(cards, seed);
  auto addedCards = std::vector<game::Card>();
  REQUIRE(deck.GetDrawPile().size() == cardAmount);
  REQUIRE(!deck.AddCards(addedCards));
  REQUIRE(deck.GetDrawPile().size() == cardAmount);
}

TEST_CASE("Add cards to an empty deck", "[addCards]") {
  unsigned int seed = 1;
  size_t cardAmount = 2;
  auto addedCards = std::vector<game::Card>();
  for (int i = 0; i < cardAmount; i++) {
    game::Card c{game::CardType::RED, static_cast<game::CardValue>(i)};
    addedCards.emplace_back(c);
  }
  auto cards = std::vector<game::Card>();
  game::Deck deck(cards, seed);
  REQUIRE(deck.AddCards(addedCards));
  REQUIRE(addedCards.size() == 0);
  REQUIRE(deck.GetDrawPile().size() == 2);
}

TEST_CASE("Add cards to a deck", "[addCards]") {
  unsigned int seed = 1;
  size_t cardAmount = 2;
  auto cards = std::vector<game::Card>();
  auto addedCards = std::vector<game::Card>();
  for (int i = 0; i < cardAmount; i++) {
    game::Card c{game::CardType::RED, static_cast<game::CardValue>(i)};
    cards.emplace_back(c);
    addedCards.emplace_back(c);
  }
  game::Deck deck(cards, seed);
  REQUIRE(deck.AddCards(addedCards));
  REQUIRE(addedCards.size() == 0);
  REQUIRE(deck.GetDrawPile().size() == 4);
}

