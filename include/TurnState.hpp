#ifndef TURN_STATE_HPP
#define TURN_STATE_HPP

#include "Card.hpp"

namespace game {
  namespace turn {
    enum State {
      ACTIVE,
      MOVE,
      CHANGE_COLOR,
      INACTIVE
    };
  
    class TurnState {
      public:
        /**
         * @brief Change State to active
         *
         * @return success if current state is inactive
         */
        bool OnEnter();

        /**
         * @brief Change state to inactive
         *
         * @return success if current state is not inactive
         */
        bool OnExit();

        /**
         * @brief handle logic changing between states based on player move
         *
         * @return determine if successful state change
         */
        bool Change(CardType type);

        State GetState() {
          return this->mState;
        }

      private:
        State mState = State::INACTIVE;
    };

  };
};

#endif

