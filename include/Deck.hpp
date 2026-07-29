#ifndef DECK_HPP
#define DECK_HPP

#include <cstdlib>
#include <cstring>
#include <random>
#include "Card.hpp"

namespace game {
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

      Card* GetDrawPile() {
        return this->mDrawPile;
      }

      unsigned int GetDrawPileSize() {
        return this->mDrawPileSize;
      }

      Card* GetDiscardPile() {
        return this->mDiscardPile;
      }

      unsigned int GetDiscardPileSize() {
        return this->mDiscardPileSize;
      }

    private:
      Card* mDrawPile = nullptr;
      Card* mDiscardPile = nullptr;
      unsigned int mDrawPileSize;
      unsigned int mDiscardPileSize;
      std::mt19937 mSeed;
  };
};

#endif
