#include "DrawCore.hpp"
#include <catch2/catch_test_macros.hpp>
#include <spdlog/spdlog.h>

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

TEST_CASE("[dealCards]") {
  SECTION("Dealing small deck to small playerCount") {
    spdlog::info("[CoreTest] [dealCards]");
    unsigned int seed = 1;
    size_t playerCount = 2;

    game::DrawCore game = game::DrawCore(seed, playerCount);
    REQUIRE(!game.DealCards(20));
  }

  SECTION("Dealing full deck to 8 players") {
    spdlog::info("[CoreTest] [dealCards]");
    unsigned int seed = 1;
    size_t playerCount = 8;
    auto cards = GenerateDeck();
    game::DrawCore game = game::DrawCore(seed, playerCount, cards);
    REQUIRE(game.DealCards(20));
  }
}

TEST_CASE("[makeMove]" ) {
  SECTION("RESIGN") {
    spdlog::info("[CoreTest] [makeMove]");
    unsigned int seed = 1;
    size_t playerCount = 2;
    auto cards = GenerateDeck();
    game::DrawCore game = game::DrawCore(seed, playerCount, cards);
    REQUIRE(game.DealCards(2));
    auto move = game::Move{game::MoveType::RESIGN, 0, std::nullopt};
    REQUIRE(game.MakeMove(move));
    auto players = game.GetPlayers();
    REQUIRE(players);
    REQUIRE(players.value().size() == 1);
    REQUIRE(players.value().back().GetState() == game::turn::State::ACTIVE);
    REQUIRE(game.GetLosers());
    REQUIRE(game.GetLosers().value().size() > 0);
    REQUIRE(game.GetLosers().value()[0] == 0);
  }

  SECTION("Play Card Reverse") {
    spdlog::info("[CoreTest] [makeMove]");
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
    auto move = game::Move{game::MoveType::PLAY_CARD, 0, cards[1]};
    REQUIRE(game.MakeMove(move));
    auto players = game.GetPlayers();
    REQUIRE(players);
    REQUIRE(players.value().back().GetState() == game::turn::State::ACTIVE);
  }

  SECTION("Play Card Skip") {
    spdlog::info("[CoreTest] [makeMove]");
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
    auto move = game::Move{game::MoveType::PLAY_CARD, 0, cards[1]};
    REQUIRE(game.MakeMove(move));
    auto players = game.GetPlayers();
    REQUIRE(players);
    REQUIRE(players.value()[2].GetState() == game::turn::State::ACTIVE);
  }

  SECTION("Play Card Regular Card") {
    spdlog::info("[CoreTest] [makeMove]");
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
    auto move = game::Move{game::MoveType::PLAY_CARD, 0, cards[1]};
    REQUIRE(game.MakeMove(move));
    auto players = game.GetPlayers();
    REQUIRE(players);
    REQUIRE(players.value()[1].GetState() == game::turn::State::ACTIVE);
  }

  SECTION("Play Card Regular, Reverse") {
    spdlog::info("[CoreTest] [makeMove]");
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
    REQUIRE(game.MakeMove(game::Move{game::MoveType::PLAY_CARD, 0, game::Card{game::CardType::RED, game::CardValue::ZERO}}));
    REQUIRE(game.GetPlayers().value()[1].GetState() == game::turn::ACTIVE);
    REQUIRE(game.MakeMove(game::Move{game::MoveType::PLAY_CARD, 1, game::Card{game::CardType::RED, game::CardValue::REVERSE}}));
  }

  SECTION("Play Card Draw 2 no stacking possible") {
    spdlog::info("[CoreTest] [makeMove]");
    unsigned int seed = 1;
    size_t playerCount = 4;
    auto cards = std::vector<game::Card>();
    cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::PLUS_TWO});
    cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
    cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
    cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
    cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
    cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
    cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
    cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
    cards.emplace_back(game::Card{game::CardType::RED, game::CardValue::ZERO});
    game::DrawCore game = game::DrawCore(seed, playerCount, cards);
    REQUIRE(game.DealCards(4));
    REQUIRE(game.GetDeck().GetDrawPile().size() > 2);
    REQUIRE(game.MakeMove(game::Move{game::MoveType::PLAY_CARD, 0, game::Card{game::CardType::RED, game::CardValue::ZERO}}));
    REQUIRE(game.GetPlayers().value()[1].GetState() == game::turn::ACTIVE);
    int before = game.GetPlayers().value()[2].GetCards().value().size();
    REQUIRE(game.MakeMove(game::Move{game::MoveType::PLAY_CARD, 1, game::Card{game::CardType::RED, game::CardValue::PLUS_TWO}}));
    REQUIRE(game.GetPlayers().value()[3].GetState() == game::turn::ACTIVE);
    REQUIRE(game.GetPlayers().value()[2].GetCards().value().size() == before + 2);
  }
}
