#include "Player.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("[AddCards] [Player]") {
  auto deck = game::Deck(std::vector<game::Card>());
  auto player = game::Player(deck, 0);
  SECTION("Single") {
    auto card = game::Card{game::CardType::RED, game::CardValue::ZERO};
    player.AddCards(card);
    REQUIRE(player.GetCards(game::CardType::RED).GetCards().size()    == 1);
    REQUIRE(player.GetCards(game::CardType::GREEN).GetCards().size()  == 0);
    REQUIRE(player.GetCards(game::CardType::BLUE).GetCards().size()   == 0);
    REQUIRE(player.GetCards(game::CardType::YELLOW).GetCards().size() == 0);
    REQUIRE(player.GetCards(game::CardType::WILD).GetCards().size()   == 0);
  }
  SECTION("Multiple") {
    auto card0 = game::Card{game::CardType::RED, game::CardValue::ZERO};
    auto card1 = game::Card{game::CardType::RED, game::CardValue::ONE};
    auto cards = std::vector<game::Card>();
    cards.emplace_back(card0);
    cards.emplace_back(card1);
    player.AddCards(cards);
    REQUIRE(player.GetCards(game::CardType::RED).GetCards().size()    == 2);
    REQUIRE(player.GetCards(game::CardType::GREEN).GetCards().size()  == 0);
    REQUIRE(player.GetCards(game::CardType::BLUE).GetCards().size()   == 0);
    REQUIRE(player.GetCards(game::CardType::YELLOW).GetCards().size() == 0);
    REQUIRE(player.GetCards(game::CardType::WILD).GetCards().size()   == 0);
  }
  SECTION("None") {
    player.AddCards(std::vector<game::Card>());
    REQUIRE(player.GetCards(game::CardType::RED).GetCards().size()    == 0);
    REQUIRE(player.GetCards(game::CardType::GREEN).GetCards().size()  == 0);
    REQUIRE(player.GetCards(game::CardType::BLUE).GetCards().size()   == 0);
    REQUIRE(player.GetCards(game::CardType::YELLOW).GetCards().size() == 0);
    REQUIRE(player.GetCards(game::CardType::WILD).GetCards().size()   == 0);
  }
}

TEST_CASE("[HasCard] [Player]") {
  auto cards = std::vector<game::Card>();
  auto card = game::Card{game::CardType::RED, game::CardValue::ZERO};
  cards.emplace_back(card);
  auto deck = game::Deck(cards);
  auto player = game::Player(deck, 0);
  SECTION("Does Have") {
    REQUIRE(player.HasCard(card));
  }
  SECTION("Doesn't Have") {
    REQUIRE(!player.HasCard(game::Card{game::CardType::GREEN, game::CardValue::ZERO}));
  }
}

TEST_CASE("[PlayCard] [Player]") {
  auto deck = game::Deck(std::vector<game::Card>());
  auto player = game::Player(deck, 0);
  SECTION("Playable") {
    auto card = game::Card{game::CardType::RED, game::CardValue::ZERO};
    player.AddCards(card);
    REQUIRE(player.PlayCard(card));
  }
  SECTION("Not Playable") {
    auto card0 = game::Card{game::CardType::RED, game::CardValue::ZERO};
    auto card1 = game::Card{game::CardType::RED, game::CardValue::ONE};
    player.AddCards(card0);
    REQUIRE(!player.PlayCard(card1));
  }
  SECTION("No Cards to Play") {
    auto card = game::Card{game::CardType::RED, game::CardValue::ZERO};
    REQUIRE(!player.PlayCard(card));
  }
}
