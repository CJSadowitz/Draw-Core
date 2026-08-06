#ifndef DECK_HPP
#define DECK_HPP

#include <random>
#include "Card.hpp"
#include <optional>

namespace game {
  class Deck {
    public:
      /**
       * @brief Generates a deck obj with given cards, count and seed
       *
       * @param cards Pointer to the cards
       * @param size  Number of cards at specified location
       * @param seed  Per game instance seed value
       */
      Deck(std::vector<Card> cards, unsigned int seed);

      /**
       * @brief Returns all drawn cards until value or type matches top discard
       *
       * @return nullopt for inability to get a playable card, otherwise returns array of cards
       */
      std::optional<std::vector<Card>> DrawCards();

      /**
       * @brief Draw a single card: Useful for setting inital player hand
       *
       * @return nullopt for no cards to draw, otherwise returns the single card
       */
      std::optional<Card> DrawCard();

      /**
       * @brief On card played, resign or loss, add cards to end of draw pile and shuffle
       *
       * @param cards  takes an array of cards to add
       * @param amount any number of cards greater than or equal to 1
       */
      bool AddCards(std::vector<Card>& cards);

      /**
       * @brief Shuffles the cards in the draw pile through Fisher-Yates Alg
       */
      void ShuffleCards();

      /**
       * @brief Reshuffles discard pile back into draw, placing a single card on the top of discard
       *
       * @return successful reset; on false means there is only 1 card in discard and cannot be put into draw pile
       */
      bool ResetDiscardPile();

      /**
       * @brief Adds played card to the top of the discard pile
       *
       * @return successful card played
       */
      bool PlayCard(Card card);

      /**
       * @brief Checks to see if the card is allowed to be played on top of the discard pile
       *
       * @return fails if type or value doesn't match top of discard
       */
      bool IsLegalCard(Card card);

      /**
       * @brief places a temp card on discard pile that swaps the color
       *
       * @return fails if top discard is not a wild card
       */
      bool ChangeColor(Card card);

      std::vector<Card> GetDrawPile() {
        return this->mDrawPile;
      }

      std::vector<Card> GetDiscardPile() {
        return this->mDiscardPile;
      }

    private:
      std::vector<Card> mDrawPile;
      std::vector<Card> mDiscardPile;
      std::mt19937 mSeed;
  };
};

#endif
