#include "Card.hpp"
#include "Player.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Add no cards", "[addCards]") {
  auto cards = std::vector<game::Card>();
  game::Player p = game::Player(std::vector<game::Card>());
  REQUIRE(!p.AddCards(cards));
}

TEST_CASE("Add one of each card type", "[addCards]") {
  auto cards = std::vector<game::Card>();
  cards.emplace_back(game::Card{game::CardType::RED,    game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::GREEN,  game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::BLUE,   game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::YELLOW, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::WILD,   game::CardValue::CHANGE_COLOR});

  game::Player p = game::Player(std::vector<game::Card>());
  REQUIRE(p.AddCards(cards));
  auto allCards = p.GetCards();
  REQUIRE(allCards);
  auto rCards = p.GetCards(game::CardType::RED);
  REQUIRE(rCards);
  auto gCards = p.GetCards(game::CardType::GREEN);
  REQUIRE(gCards);
  auto bCards = p.GetCards(game::CardType::BLUE);
  REQUIRE(bCards);
  auto yCards = p.GetCards(game::CardType::YELLOW);
  REQUIRE(yCards);
  auto wCards = p.GetCards(game::CardType::WILD);
  REQUIRE(wCards);
  REQUIRE(
      allCards.value().size() == rCards.value().size() +
                                 gCards.value().size() +
                                 bCards.value().size() +
                                 yCards.value().size() +
                                 wCards.value().size());
}

TEST_CASE("Play card with no card of given type", "[playCard]") {
  game::Player p = game::Player(std::vector<game::Card>());
  REQUIRE(!p.GetCards());
  REQUIRE(!p.PlayCard(game::CardType::RED));
}

TEST_CASE("Play card with one card of the given type", "[playCard]") {
  auto cards = std::vector<game::Card>();
  cards.emplace_back(game::Card{game::CardType::RED,    game::CardValue::ZERO});
  game::Player p = game::Player(cards);
  REQUIRE(p.GetCards());
  REQUIRE(p.GetCards(game::CardType::RED));
  REQUIRE(p.PlayCard(game::CardType::RED));
  REQUIRE(!p.GetCards());
  REQUIRE(!p.GetCards(game::CardType::RED));
}

