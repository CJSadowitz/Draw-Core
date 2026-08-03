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
      DrawCore(unsigned int seed, size_t playerCount, std::vector<Card> cards = std::vector<Card>());

      bool DealCards(unsigned int minimumDeckSize);

      void PlayCard(Card card);

      unsigned int GetPlayerTurn();

      void AddPlayer(Player player);

      void RemovePlayer(Player player);

      void SetDrawPile(std::vector<Card> cards);

      void GenerateGame();

    private:
      turn::TurnState mPlayerTurn;
      Deck mDeck;
      std::vector<Player> mPlayers;
  };

};

#endif

