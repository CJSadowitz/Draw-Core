#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "TurnState.hpp"
#include <cstdio>
#include <random>

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
      /**
       * @brief Generates a deck obj with given cards, count and seed
       *
       * @param cards Pointer to the cards
       * @param size  Number of cards at specified location
       * @param seed  Per game instance seed value
       *
       */
      Deck(Card* cards, size_t size, unsigned int seed);

      ~Deck();

      Card* DrawCards();

      void AddCards(Card* cards, size_t amount);

      /**
       * @brief Shuffles the cards in the draw pile through Fisher-Yates Alg
       *
       * Current O(n^2) implementation instead of O(n)
       * Generates a new array for each element removed, reduced by one element
       */
      void ShuffleCards();

      void ResetDiscardPile();

    private:
      Card* mDrawPile;
      Card* mDiscardPile;
      unsigned int mDrawPileSize;
      unsigned int mDiscardPileSize;
      std::mt19937 mSeed;
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

