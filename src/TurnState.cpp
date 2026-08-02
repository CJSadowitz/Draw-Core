#include "TurnState.hpp"

namespace game {
  namespace turn {
    bool TurnState::OnEnter() {
      if (this->mState == State::INACTIVE) {
        this->mState = State::ACTIVE;
        return true;
      }
      return false;
    }

    bool TurnState::OnExit() {
      if (this->mState != State::INACTIVE) {
        this->mState = State::INACTIVE;
        return true;
      }
      return false;
    }

    bool TurnState::Change(CardType type) {
      if (this->mState != State::ACTIVE) {
        return false;
      }
      switch (type) {
        case(WILD):
          this->mState = State::CHANGE_COLOR;
          return true;
        default:
          this->OnExit();
          return true;
      }
    }
  };
};

