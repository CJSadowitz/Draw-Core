#include "DrawCore.hpp"

namespace game {
  DrawCore::DrawCore(unsigned int seed, size_t playerCount, std::vector<Card> cards) :
      mDeck(cards, seed) {
    for (int i = 0; i < playerCount; i++) {
      this->mPlayers.emplace_back(Player(std::vector<game::Card>()));
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
    switch(playerMove.type) {
      case(MoveType::DRAW):
        if(!this->PlayDraw()) {
          auto player = this->GetActivePlayer();
          if (!player) {
            return false;
          }
          this->RemovePlayer();
          return false;
        }
          // update next player turn
        break;
      case(MoveType::PLAY_CARD):
        if (this->PlayCard(playerMove.card)) {
          // Update next player turn + process wild or stacking
        }
        break;
      case(MoveType::CHOOSE_COLOR):
        // Expects card of not wild with chng color attrib
        this->mDeck.PlayCard(playerMove.card);
        break;
      case(MoveType::RESIGN):
        auto player = this->GetActivePlayer();
        if (!player) {
          return false;
        }
        this->RemovePlayer();
        // Update next player turn
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
      if (player.GetTurnState() != turn::State::ACTIVE) {
        return player;
      }
    }
    return std::nullopt;
  }
};

