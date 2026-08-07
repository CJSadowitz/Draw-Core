#include "DrawCore.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Dealing small deck to small playerCount", "[dealCards]") {
  unsigned int seed = 1;
  size_t playerCount = 2;

  game::DrawCore game = game::DrawCore(seed, playerCount);
  REQUIRE(!game.DealCards(20));
}

TEST_CASE("Dealing full deck to 8 players", "[dealCards]") {
  unsigned int seed = 1;
  size_t playerCount = 8;
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
  REQUIRE(cards.size() == 108);
  game::DrawCore game = game::DrawCore(seed, playerCount, cards);
  REQUIRE(game.DealCards(20));
}

TEST_CASE("Resign", "[makeMove]" ) {
  unsigned int seed = 1;
  size_t playerCount = 2;
  auto cards = std::vector<game::Card>();
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ONE});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ONE});
  game::DrawCore game = game::DrawCore(seed, playerCount, cards);
  REQUIRE(game.DealCards(2));
  auto move = game::Move{game::MoveType::RESIGN, std::nullopt};
  REQUIRE(game.MakeMove(move));
  auto players = game.GetPlayers();
  REQUIRE(players);
  REQUIRE(players.value().size() == 1);
  REQUIRE(players.value().end()->GetTurnState() == game::turn::State::ACTIVE);
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
  REQUIRE(players.value().back().GetTurnState() == game::turn::State::ACTIVE);
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
  REQUIRE(players.value()[2].GetTurnState() == game::turn::State::ACTIVE);
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
  REQUIRE(players.value()[1].GetTurnState() == game::turn::State::ACTIVE);
}

TEST_CASE("Play Card Reverse, Regular", "[makeMove]" ) {
  unsigned int seed = 1;
  size_t playerCount = 4;
  auto cards = std::vector<game::Card>();
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::REVERSE});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::REVERSE});
  cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
  game::DrawCore game = game::DrawCore(seed, playerCount, cards);
  REQUIRE(game.DealCards(2));
  REQUIRE(game.MakeMove(game::Move{game::MoveType::PLAY_CARD, cards[0]}));
  REQUIRE(game.MakeMove(game::Move{game::MoveType::PLAY_CARD, cards[0]}));
  REQUIRE(game.MakeMove(game::Move{game::MoveType::PLAY_CARD, cards[0]}));
  REQUIRE(game.MakeMove(game::Move{game::MoveType::PLAY_CARD, cards[0]}));
}
