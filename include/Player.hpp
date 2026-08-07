#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Card.hpp"
#include <vector>
#include <optional>

namespace game {
  namespace turn {
    enum State {
      ACTIVE,
      INACTIVE,
      CHANGE_COLOR,
      PLAYDRAW,
      PLAYSTACK
    };
  }
  class Player {
    public:
      Player(std::vector<Card> cards, int id);

      /**
       * @brief After a draw move, cards need to be added to hand
       *
       * @param cards The vector of cards from 1-n, 0 returns false
       * @return bool of success
       */
      bool AddCards(std::vector<Card> cards);

      /**
       * @brief Helper function for adding a single card to any section
       */
      void AddCard(Card card);

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
      std::optional<std::vector<Card>> GetCards(CardType type);

      /**
       * @brief returns all cards of a player's hand if it exists
       *
       * @return mCards if exists
       */
      std::optional<std::vector<Card>> GetCards();

      /**
       * @brief determines if the passed in card is on the top of any pile
       *
       * @return true if the card exists
       */
      bool HasCard(Card card);

      /**
       *
       */
      void SetState(turn::State state) {
        this->mState = state;
      }

      turn::State GetState() {
        return this->mState;
      }

      int GetId() {
        return this->mId;
      }

      bool operator==(const Player& other) const {
        return this->mId == other.mId;
      }

    private:
      int mId;
      turn::State mState;
      std::vector<Card> mCards;
      // How can I not hardcode the han to have certain card types?
      std::vector<Card> mRedCards;
      std::vector<Card> mGreenCards;
      std::vector<Card> mBlueCards;
      std::vector<Card> mYellowCards;
      std::vector<Card> mWildCards;
  };
}

#endif

