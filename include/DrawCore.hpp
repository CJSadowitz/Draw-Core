#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "TurnState.hpp"
#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include <cstdio>

namespace game {
  class DrawCore {
    public:
      DrawCore(unsigned int seed, size_t playerCount);

      void PlayCard(Card card);

      unsigned int GetPlayerTurn();

    private:

      void GenerateGame();

      unsigned int mSeed;
      turn::TurnState mPlayerTurn;
      Deck* mDeck;
      Player mPlayers[];
  };

};

#endif

