#include "DrawCore.hpp"
#include <algorithm>
#include <iterator>

namespace game {
  DrawCore::DrawCore(unsigned int seed, size_t playerCount, std::vector<Card> cards) :
      mDeck(cards, seed) {
    for (int i = 0; i < playerCount; i++) {
      this->mPlayers.emplace_back(Player(std::vector<game::Card>(), i));
    }
    if (playerCount > 0) {
      this->mPlayers[0].SetState(turn::State::ACTIVE);
    }
  }

  bool DrawCore::DealCards(unsigned int minimumDeckSize) {
    if (this->mDeck.GetDrawPile().size() == 0 || this->mPlayers.size() <= 1) {
      return false;
    }
    unsigned int playerIndex = 0;
    this->mDeck.ShuffleCards();
    for (int i = this->mDeck.GetDrawPile().size(); i > minimumDeckSize; i--) {
      auto card = this->mDeck.DrawCard();
      if (!card) {
        break;
      }
      this->mPlayers[playerIndex].AddCard(card.value());
      playerIndex = (playerIndex + 1) % this->mPlayers.size();
    }
    return this->mDeck.ResetDiscardPile();
  }

  bool DrawCore::MakeMove(Move playerMove) {
    auto player = this->GetActivePlayer();
    if (!player) {
      return false;
    }
    switch(playerMove.type) {
      case(MoveType::DRAW):
        if(!this->PlayDraw()) {
          this->RemovePlayer();
          return false;
        }
        this->UpdateTurn(turn::TurnType::DRAW);
        break;
      case(MoveType::PLAY_CARD):
        if (!playerMove.card) {
          return false;
        }
        if (!this->mDeck.IsLegalCard(playerMove.card.value()) || !this->IsLegalCard(playerMove.card.value())) {
          return false;
        }
        // Already handled placement of card and removal of card from player hand
        if (this->PlayCard(playerMove.card.value()) && this->mDeck.PlayCard(playerMove.card.value())) {
          // wild
          if (playerMove.card.value().type == CardType::WILD) {
            this->UpdateTurn(turn::TurnType::CHANGECOLOR);
          }
          if (playerMove.card.value().value == CardValue::PLUS_TWO) {
            this->UpdateTurn(turn::TurnType::STACK);
          }
          if (playerMove.card.value().value == CardValue::REVERSE) {
            this->UpdateTurn(turn::TurnType::REVERSE);
            return true;
          }
          if (playerMove.card.value().value == CardValue::SKIP) {
            this->UpdateTurn(turn::TurnType::SKIP);
            return true;
          }
          // default regular card
          auto activeIt = std::find(this->mPlayers.begin(), this->mPlayers.end(), player.value());
          int activeIndex = std::distance(this->mPlayers.begin(), activeIt);
          int nextActiveIndex = (activeIndex + this->mDirection) % this->mPlayers.size();
          auto nextActivePlayer = this->mPlayers[nextActiveIndex];

          nextActivePlayer.SetState(turn::State::ACTIVE);
          this->mPlayers[activeIndex] = player.value();
          this->mPlayers[nextActiveIndex] = nextActivePlayer;
          return true;
        }
        return true;
        break;
      case(MoveType::CHOOSE_COLOR):
        // Expects card of not wild with chng color attrib
        if (!playerMove.card) {
          return false;
        }
        
        this->mDeck.PlayCard(playerMove.card.value());
        break;
      case(MoveType::RESIGN):
        // Find the location of the active player
        auto activeIt = std::find(this->mPlayers.begin(), this->mPlayers.end(), player.value());
        int activeIndex = std::distance(this->mPlayers.begin(), activeIt);
        int nextActiveIndex = (activeIndex + this->mDirection) % this->mPlayers.size();
        auto nextActivePlayer = this->mPlayers[nextActiveIndex];

        this->RemovePlayer();

        // After removing from the list, update new player to active and replace them in the list
        auto nextActiveIt = std::find(this->mPlayers.begin(), this->mPlayers.end(), nextActivePlayer);
        nextActiveIndex = std::distance(this->mPlayers.begin(), nextActiveIt);
        nextActivePlayer.SetState(turn::State::ACTIVE);
        this->mPlayers[nextActiveIndex] = nextActivePlayer;

        this->mLosers.emplace_back(player.value().GetId());
        break;
    }
    return true;
  }

  void DrawCore::RemovePlayer() {
    auto newPlayers = std::vector<Player>();
    for (auto player : this->mPlayers) {
      if (player.GetState() != turn::State::ACTIVE) {
        newPlayers.emplace_back(player);
      }
    }
    this->mPlayers = newPlayers;
  }

  bool DrawCore::PlayDraw() {
    auto player = this->GetActivePlayer();
    auto cards = this->mDeck.DrawCards();
    if (!cards && !player) {
      return false;
    }
    player.value().AddCards(cards.value());
    return true;
  }

  bool DrawCore::PlayCard(game::Card card) {
    if (!this->IsLegalCard(card)) {
      return false;
    }
    auto player = this->GetActivePlayer();
    // Card was played and added to the deck and removed from player hand
    // PlayCard should always be true because of the IsLegalCard Check
    if (this->mDeck.PlayCard(card) && player.value().PlayCard(card)) {
      return true;
    }
    return false;
  }

  bool DrawCore::IsLegalCard(game::Card card) {
    auto player = this->GetActivePlayer();
    if (!player) {
      return false;
    }
    return player.value().HasCard(card);
  }

  std::optional<game::Player> DrawCore::GetActivePlayer() {
    if (this->mPlayers.size() == 0) {
      return std::nullopt;
    }
    for (auto player : this->mPlayers) {
      if (player.GetState() == turn::State::ACTIVE) {
        return player;
      }
    }
    return std::nullopt;
  }

  void DrawCore::UpdateTurn(turn::TurnType type) {
    auto player = this->GetActivePlayer();
    if (!player) {
      return;
    }
    int dir = 0;
    switch (type) {
      case (turn::TurnType::DEFAULT):
        dir = this->mDirection;
        break;
      case (turn::TurnType::REVERSE):
        this->mDirection = static_cast<turn::TurnDirection>(this->mDirection * -1);
        dir = this->mDirection;
        break;
      case (turn::TurnType::SKIP):
        dir = this->mDirection * 2;
        break;
      case (turn::TurnType::CHANGECOLOR):
        player.value().SetState(turn::State::CHANGE_COLOR);
        return;
      case (turn::TurnType::DRAW):
        player.value().SetState(turn::State::PLAYDRAW);
        return;
      case (turn::TurnType::STACK):
        player.value().SetState(turn::State::PLAYSTACK);
        return;
    }

    auto activeIt = std::find(this->mPlayers.begin(), this->mPlayers.end(), player.value());
    int activeIndex = std::distance(this->mPlayers.begin(), activeIt);
    int nextActiveIndex = (activeIndex + dir) % this->mPlayers.size();
    auto nextActivePlayer = this->mPlayers[nextActiveIndex];
    player.value().SetState(turn::State::INACTIVE);
    nextActivePlayer.SetState(turn::State::ACTIVE);
    this->mPlayers[activeIndex] = player.value();
    this->mPlayers[nextActiveIndex] = nextActivePlayer;
  }
};

