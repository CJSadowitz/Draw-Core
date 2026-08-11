#include "DrawCore.hpp"
#include <algorithm>
#include <iterator>
#include <spdlog/spdlog.h>

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

  /**
   * All main logic is routed through this method
   *
   * Every player move, updated winner and loser positions, and turns
   */
  bool DrawCore::MakeMove(Move playerMove) {
    auto player = this->GetActivePlayer();
    if (!player || playerMove.playerId != player.value().GetId()) {
      return false;
    }
    switch(playerMove.type) {
      case (MoveType::RESIGN):
        this->mLosers.emplace_back(playerMove.playerId);
        this->UpdateTurn(turn::TurnType::DEFAULT);
        this->RemovePlayer(playerMove.playerId);
        break;
      case (MoveType::PLAY_CARD):
        if (!playerMove.card) {
          return false;
        }
        this->PlayCard(playerMove.card.value());
        this->UpdateTurn(playerMove.card.value());
        break;
      case (MoveType::DRAW):
        if (!this->PlayDraw()) {
          this->mLosers.emplace_back(playerMove.playerId);
        }
        this->UpdateTurn(turn::TurnType::DRAW);
        break;
      case (MoveType::CHOOSE_COLOR):
        break;
    }
    return true;
  }

  void DrawCore::RemovePlayer(int playerId) {
    auto newPlayers = std::vector<Player>();
    for (auto player : this->mPlayers) {
      if (player.GetId() != playerId) {
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

  void DrawCore::UpdateTurn(Card playedCard) {
    if (playedCard.type == CardType::WILD) {

    }
    else if (playedCard.value == CardValue::REVERSE) {
      this->UpdateTurn(turn::TurnType::REVERSE);
    }
    else if (playedCard.value == CardValue::SKIP) {
      this->UpdateTurn(turn::TurnType::SKIP);
    }
    else {
      this->UpdateTurn(turn::TurnType::DEFAULT);
    }
  }
};

