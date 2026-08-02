#include "TurnState.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("State changing when next player is active", "[onEnter]") {
  game::turn::TurnState ts;
  REQUIRE(ts.GetState() == game::turn::State::INACTIVE);
  REQUIRE(ts.OnEnter());
  REQUIRE(ts.GetState() == game::turn::State::ACTIVE);
  REQUIRE(!ts.OnEnter());
}

TEST_CASE("State change to exit status", "[onExit]") {
  game::turn::TurnState ts;
  REQUIRE(ts.GetState() == game::turn::State::INACTIVE);
  REQUIRE(!ts.OnExit());
}

TEST_CASE("Change state when card played", "[onChange]") {
  game::turn::TurnState ts;
  REQUIRE(ts.GetState() == game::turn::State::INACTIVE);
  REQUIRE(ts.OnEnter());
  REQUIRE(ts.Change(game::CardType::RED));
  REQUIRE(ts.GetState() == game::turn::State::INACTIVE);
  REQUIRE(!ts.OnExit());
}

TEST_CASE("Change state when wild card played", "[onChange]") {
  game::turn::TurnState ts;
  REQUIRE(ts.GetState() == game::turn::State::INACTIVE);
  REQUIRE(ts.OnEnter());
  REQUIRE(ts.Change(game::CardType::WILD));
  REQUIRE(ts.GetState() == game::turn::State::CHANGE_COLOR);
  REQUIRE(!ts.OnEnter());
  REQUIRE(ts.OnExit());
}

