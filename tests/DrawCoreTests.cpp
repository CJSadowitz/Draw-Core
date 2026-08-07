#include "DrawCore.hpp"
#include <catch2/catch_test_macros.hpp>
#include <iostream>

std::vector<game::Card> GenerateDeck() {
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
  return cards;
}

TEST_CASE("Dealing small deck to small playerCount", "[dealCards]") {
  unsigned int seed = 1;
  size_t playerCount = 2;

  game::DrawCore game = game::DrawCore(seed, playerCount);
  REQUIRE(!game.DealCards(20));
}

TEST_CASE("Dealing full deck to 8 players", "[dealCards]") {
  unsigned int seed = 1;
  size_t playerCount = 8;
  auto cards = GenerateDeck();
  game::DrawCore game = game::DrawCore(seed, playerCount, cards);
  REQUIRE(game.DealCards(20));
}

TEST_CASE("Resign", "[makeMove]" ) {
  unsigned int seed = 1;
  size_t playerCount = 2;
  auto cards = GenerateDeck();
  game::DrawCore game = game::DrawCore(seed, playerCount, cards);
  REQUIRE(game.DealCards(2));
  auto move = game::Move{game::MoveType::RESIGN, std::nullopt};
  REQUIRE(game.MakeMove(move));
  auto players = game.GetPlayers();
  REQUIRE(players);
  REQUIRE(players.value().size() == 1);
  REQUIRE(players.value().back().GetState() == game::turn::State::ACTIVE);
  REQUIRE(game.GetLosers());
  REQUIRE(game.GetLosers().value().size() > 0);
  REQUIRE(game.GetLosers().value()[0] == 0);
}

TEST_CASE("Play Card Reverse", "[makeMove]" ) {
  unsigned int seed = 1;
  size_t playerCount = 4;
  auto cards = std::vector<game::Card>();
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::REVERSE});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::REVERSE});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::REVERSE});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::REVERSE});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::REVERSE});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::REVERSE});
  game::DrawCore game = game::DrawCore(seed, playerCount, cards);
  REQUIRE(game.DealCards(2));
  auto move = game::Move{game::MoveType::PLAY_CARD, cards[1]};
  REQUIRE(game.MakeMove(move));
  auto players = game.GetPlayers();
  REQUIRE(players);
  REQUIRE(players.value().back().GetState() == game::turn::State::ACTIVE);
}

TEST_CASE("Play Card Skip", "[makeMove]" ) {
  unsigned int seed = 1;
  size_t playerCount = 4;
  auto cards = std::vector<game::Card>();
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::SKIP});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::SKIP});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::SKIP});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::SKIP});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::SKIP});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::SKIP});
  game::DrawCore game = game::DrawCore(seed, playerCount, cards);
  REQUIRE(game.DealCards(2));
  auto move = game::Move{game::MoveType::PLAY_CARD, cards[1]};
  REQUIRE(game.MakeMove(move));
  auto players = game.GetPlayers();
  REQUIRE(players);
  REQUIRE(players.value()[2].GetState() == game::turn::State::ACTIVE);
}

TEST_CASE("Play Card Regular Card", "[makeMove]" ) {
  unsigned int seed = 1;
  size_t playerCount = 4;
  auto cards = std::vector<game::Card>();
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  game::DrawCore game = game::DrawCore(seed, playerCount, cards);
  REQUIRE(game.DealCards(2));
  auto move = game::Move{game::MoveType::PLAY_CARD, cards[1]};
  REQUIRE(game.MakeMove(move));
  auto players = game.GetPlayers();
  REQUIRE(players);
  REQUIRE(players.value()[1].GetState() == game::turn::State::ACTIVE);
}

TEST_CASE("Play Card Regular, Reverse, Regular", "[makeMove]" ) {
  unsigned int seed = 1;
  size_t playerCount = 4;
  auto cards = std::vector<game::Card>();
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::REVERSE});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  game::DrawCore game = game::DrawCore(seed, playerCount, cards);
  REQUIRE(game.DealCards(2));
 
  auto players = game.GetPlayers().value();
  for (auto player : players) {
    auto playerCards = player.GetCards();
    if(!playerCards) {
      std::cout << "WTF!\n";
    }
    std::cout << "Player n\n";
    for (auto card : playerCards.value()) {
      std::cout << card.type << ' ' << card.value << '\n';
    }
  }
  
  REQUIRE(game.MakeMove(game::Move{game::MoveType::PLAY_CARD, game::Card{game::CardType::RED, game::CardValue::ZERO}}));
  REQUIRE(game.GetPlayers().value()[1].GetState() == game::turn::ACTIVE);
  auto playerCards = game.GetPlayers().value()[1].GetCards();
  for (auto card : playerCards.value()) {
      std::cout << card.type << ' ' << card.value << '\n';
  }
  REQUIRE(game.MakeMove(game::Move{game::MoveType::PLAY_CARD, game::Card{game::CardType::RED, game::CardValue::REVERSE}}));
}

