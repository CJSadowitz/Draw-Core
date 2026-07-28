#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include <cstdio>
#include "TurnState.hpp"

namespace game {
  enum CardType {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WILD
  };

  enum CardValue {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    SKIP,
    PLUS_TWO,
    REVERSE,
    CHANGE_COLOR,
    CHANGE_COLOR_PLUS_FOUR
  };

  struct Card {
    CardType type;
    CardValue value;
  };

  class Deck {
    public:
      Deck(Card* cards, size_t size);

      Card* DrawCards();

      void AddCards(Card* cards, size_t amount);

      void ResetDiscardPile();

    private:
      Card* mDrawPile;
      Card* mDiscardPile;
  };

  class Player {
    public:
      Player(Card* cards, size_t size);

      Card* GetCards(CardType type);

      void AddCard(Card card);

      void RemoveCard(Card card);

    private:
      Card* mCards;
  };

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

