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
};

