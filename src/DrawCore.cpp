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
    // Hardcoded alg for classic draw game
    size_t cardAmount = this->mDeck.GetDrawPile().size();
    unsigned int playerIndex = 0;
    do {
      auto card = this->mDeck.DrawCard();
      if (card) {
        this->mPlayers[playerIndex].AddCard(card.value());
        cardAmount--;
      }
      else {
        break;
      }
      playerIndex += 1 % this->mPlayers.size();
    } while(cardAmount > minimumDeckSize);
    return true;
  }

  bool DrawCore::PlayCard(game::Card card) {
    if (!this->IsLegalCard(card)) {
      return false;
    }
    auto player = this->GetActivePlayer();
    if (this->mDeck.PlayCard(card) && player.value().PlayCard(card)) {
      // Change next player state to active, and card effects
    }
    return true;
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

