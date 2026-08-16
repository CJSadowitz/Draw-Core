#ifndef DECK_HPP
#define DECK_HPP


#include "Card.hpp"
#include <optional>

namespace game {
  class Deck {
    public:
      /**
       * @brief Generates a deck obj with given cards, count and seed
       *
       * @param cards vector to the cards
       */
      Deck(std::vector<Card> cards = std::vector<Card>());

      /**
       * @brief Returns all drawn cards until value or type matches top discard
       *
       * @return nullopt for inability to get a playable card, otherwise returns array of cards
       */
      std::optional<std::vector<Card>> DrawCards(int count);

      /**
       * @brief On card played, resign or loss, add cards to end of draw pile and shuffle
       *
       * @param cards  takes an array of cards to add
       */
      void AddCards(std::vector<Card> cards);
      void AddCards(Card card);

      /**
       * @brief Adds played card to the top of the discard pile
       *
       * @return successful card played
       */
      std::optional<Card> PlayCard(Card card);

      /**
       * @brief Checks to see if the card is allowed to be played on top of the discard pile
       *
       * @return fails if type or value doesn't match top of discard
       */
      bool HasCard(Card card);

      std::vector<Card> GetCards() { return this->mCards; }

    private:
      std::vector<Card> mCards;
  };
};

#endif
