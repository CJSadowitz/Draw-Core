#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include <cstdio>

namespace game {
  class DrawCore {
    public:
      DrawCore(unsigned int seed, size_t playerCount, std::vector<Card> cards = std::vector<Card>());

      bool DealCards(unsigned int minimumDeckSize);

      bool PlayCard(Card card);

      bool IsLegalCard(Card card);

      std::optional<Player> GetActivePlayer();

      void AddPlayer(Player player);

      void RemovePlayer(Player player);

      void SetDrawPile(std::vector<Card> cards);

      void GenerateGame();

    private:
      Deck mDeck;
      bool mStacking = false;
      int mStackCount = 0;
      std::vector<Player> mPlayers;
  };

};

#endif

