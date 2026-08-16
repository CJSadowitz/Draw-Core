#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <optional>
#include "Deck.hpp"
#include "Card.hpp"

namespace game {
  class Player {
    public:
      Player(Deck cards, int id);

      /**
       * @brief After a draw move, cards need to be added to hand
       *
       * @param cards The vector of cards from 1-n, 0 returns false
       * @return bool of success
       */
      void AddCards(std::vector<Card> cards);
      void AddCards(Card card);

      /**
       * @brief removes and returns the top most playable card
       *
       * @return returns the card or null if there is none
       */
      std::optional<Card> PlayCard(Card pCard);

      /**
       * @brief returns the array of cards of specified type
       *
       * @return an optional array if cards of specified type exist
       */
      Deck GetCards(CardType type);

      /**
       * @brief determines if the passed in card is on the top of any pile
       *
       * @return true if the card exists
       */
      bool HasCard(Card card);

      int GetId() { return this->mId; }

      bool operator==(const Player& other) const { return this->mId == other.mId; }

    private:
      int mId;
      Deck mRedCards;
      Deck mGreenCards;
      Deck mBlueCards;
      Deck mYellowCards;
      Deck mWildCards;
  };
}

#endif
