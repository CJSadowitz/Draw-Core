#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include <cstdio>

namespace game {
  enum TurnDirection {
    FORWARD,
    BACKWARD
  };
  enum MoveType {
    DRAW,
    PLAY_CARD,
    CHOOSE_COLOR,
    RESIGN
  };
  struct Move {
    MoveType type;
    Card card;
  };
  class DrawCore {
    public:
      DrawCore(unsigned int seed, size_t playerCount, std::vector<Card> cards = std::vector<Card>());

      /**
       * @brief Deals cards one at a time after shuffling until draw pile min is reached
       *
       * @param minimumDeckSize A uint value that describes the lowest the draw pile can reached
       * @return fails with no cards or no players
       */
      bool DealCards(unsigned int minimumDeckSize);

      bool MakeMove(Move playerMove);

      void AddPlayer(Player player);

      void RemovePlayer();

      void SetDrawPile(std::vector<Card> cards);

      void GenerateGame();

    private:

      bool PlayDraw();

      bool IsLegalCard(Card card);

      bool PlayCard(Card card);

      std::optional<Player> GetActivePlayer();

      Deck mDeck;
      bool mStacking = false;
      int mStackCount = 0;
      TurnDirection mDirection = FORWARD;
      std::vector<Player> mPlayers;
  };

};

#endif

