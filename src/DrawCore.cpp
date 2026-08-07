#include "DrawCore.hpp"
#include <algorithm>
#include <iterator>
#include <iostream>

namespace game {
  DrawCore::DrawCore(unsigned int seed, size_t playerCount, std::vector<Card> cards) :
      mDeck(cards, seed) {
    for (int i = 0; i < playerCount; i++) {
      this->mPlayers.emplace_back(Player(std::vector<game::Card>(), i));
    }
    if (playerCount > 0) {
      this->mPlayers[0].SetActiveTurn();
    }
  }

  bool DrawCore::DealCards(unsigned int minimumDeckSize) {
    if (this->mDeck.GetDrawPile().size() == 0 || this->mPlayers.size() <= 1) {
      return false;
    }
    size_t cardAmount = this->mDeck.GetDrawPile().size();
    unsigned int playerIndex = 0;
    this->mDeck.ShuffleCards();
    do {
      auto card = this->mDeck.DrawCard();
      if (card) {
        this->mPlayers[playerIndex].AddCard(card.value());
        cardAmount--;
      }
      else {
        break;
      }
      playerIndex = (playerIndex + 1) % (this->mPlayers.size() - 1);
    } while(cardAmount > minimumDeckSize);
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
          // update next player turn
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
            // Wow a 'well' built function already handles it!
            // Handle plus 4
            return true;
          }
          //
          // plus 2
          if (playerMove.card.value().value == CardValue::PLUS_TWO) {
            auto activeIt = std::find(this->mPlayers.begin(), this->mPlayers.end(), player.value());
            int activeIndex = std::distance(this->mPlayers.begin(), activeIt);
            int nextActiveIndex = (activeIndex + 2 * this->mDirection) % this->mPlayers.size();
            auto nextActivePlayer = this->mPlayers[nextActiveIndex];

            nextActivePlayer.SetActiveTurn();
            this->mPlayers[activeIndex] = player.value();
            this->mPlayers[nextActiveIndex] = nextActivePlayer;
            return true;
          }
          // reverse
          if (playerMove.card.value().value == CardValue::REVERSE) {
            this->mDirection = static_cast<TurnDirection>(this->mDirection * -1);
            // update player turn
            auto activeIt = std::find(this->mPlayers.begin(), this->mPlayers.end(), player.value());
            int activeIndex = std::distance(this->mPlayers.begin(), activeIt);
            int nextActiveIndex = (activeIndex + this->mDirection) % this->mPlayers.size();
            auto nextActivePlayer = this->mPlayers[nextActiveIndex];

            nextActivePlayer.SetActiveTurn();
            this->mPlayers[activeIndex] = player.value();
            this->mPlayers[nextActiveIndex] = nextActivePlayer;
            return true;
          }
          // skip
          if (playerMove.card.value().value == CardValue::SKIP) {
            auto activeIt = std::find(this->mPlayers.begin(), this->mPlayers.end(), player.value());
            int activeIndex = std::distance(this->mPlayers.begin(), activeIt);
            int nextActiveIndex = (activeIndex + 2 * this->mDirection) % this->mPlayers.size();
            auto nextActivePlayer = this->mPlayers[nextActiveIndex];

            nextActivePlayer.SetActiveTurn();
            this->mPlayers[activeIndex] = player.value();
            this->mPlayers[nextActiveIndex] = nextActivePlayer;
            return true;
          }
          // default regular card
          auto activeIt = std::find(this->mPlayers.begin(), this->mPlayers.end(), player.value());
          int activeIndex = std::distance(this->mPlayers.begin(), activeIt);
          int nextActiveIndex = (activeIndex + this->mDirection) % this->mPlayers.size();
          auto nextActivePlayer = this->mPlayers[nextActiveIndex];

          nextActivePlayer.SetActiveTurn();
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
        nextActivePlayer.SetActiveTurn();
        this->mPlayers[nextActiveIndex] = nextActivePlayer;

        this->mLosers.emplace_back(player.value().GetId());
        break;
    }
    return true;
  }

  void DrawCore::RemovePlayer() {
    auto newPlayers = std::vector<Player>();
    for (auto player : this->mPlayers) {
      if (player.GetTurnState() != turn::State::ACTIVE) {
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
      if (player.GetTurnState() == turn::State::ACTIVE) {
        return player;
      }
    }
    return std::nullopt;
  }
};

