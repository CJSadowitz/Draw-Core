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

      /**
       * @brief Returns all drawn cards until value or type matches top discard
       *
       * @return nullptr for inability to get a playable card, otherwise returns array of cards
       */
      Card* DrawCards();

      /**
       * @brief On card played, resign or loss, add cards to end of draw pile and shuffle
       *
       * @param cards  takes an array of cards to add
       * @param amount any number of cards greater than or equal to 1
       */
      void AddCards(Card* cards, size_t amount);

      /**
       * @brief Shuffles the cards in the draw pile through Fisher-Yates Alg
       */
      void ShuffleCards();

      /**
       * @brief Reshuffles discard pile back into draw, placing a single card on the top of discard
       */
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
