#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <cstdio>
#include "Card.hpp"

namespace game {
class Player {
    public:
      Player(Card* cards, size_t size);

      Card* GetCards(CardType type);

      void AddCard(Card card);

      void RemoveCard(Card card);

    private:
      Card* mCards;
  };
}

#endif

