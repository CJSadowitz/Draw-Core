#include "Deck.hpp"
#include <iostream>

namespace game {
  Deck::Deck(std::vector<Card> cards, unsigned int seed) {
    // May have to move this to Engine class
    this->mSeed.seed(seed);

    this->mDrawPile = cards;
  }

  Deck::~Deck() {}

  void Deck::ShuffleCards() {
    auto shuffledCards = std::vector<Card>();

    unsigned int totalCards = this->mDrawPile.size();
    unsigned int remainingCards = this->mDrawPile.size();
    while (remainingCards != 0) {
      std::uniform_int_distribution<int> distr(0, remainingCards - 1);
      int index = distr(this->mSeed);
      shuffledCards.emplace_back(this->mDrawPile[index]);
      this->mDrawPile[index] = this->mDrawPile[remainingCards - 1];
      remainingCards--;
    }

    this->mDrawPile = shuffledCards;
  }

  bool Deck::DrawCards(std::vector<Card>& drawnCards) { 
    if (this->mDrawPile.size() == 0 && this->mDiscardPile.size() == 0) {
      return false;
    }

    auto topCard = this->mDiscardPile[this->mDiscardPile.size() - 1];

    int i = this->mDrawPile.size() - 1;
    auto card = this->mDrawPile[i];
    this->mDrawPile.pop_back();
    bool isSameType  = card.type == topCard.type;
    bool isSameValue = card.value == topCard.value;
    bool isWildCard  = card.type == CardType::WILD;
    while (!isSameType && !isSameValue && !isWildCard) {
      if (i == 0) {
        drawnCards = std::vector<Card>();
        return false;
      }
      drawnCards.emplace_back(card);
      i--;
      card = this->mDrawPile[i];
      this->mDrawPile.pop_back();
    }

    drawnCards.emplace_back(card);
    return true;
  }

  bool Deck::ResetDiscardPile() {
    // No cards to reset
    if (this->mDiscardPile.size() == 1) {
      return false;
    }
    // Deck initialization -> add a single card to play off of
    if (this->mDiscardPile.size() == 0 && this->mDrawPile.size() > 0) {
      this->mDiscardPile.emplace_back(this->mDrawPile[this->mDrawPile.size() - 1]);
      this->mDrawPile.pop_back();
      return true;
    }

    if (this->mDiscardPile.size() == 0 && this->mDrawPile.size() == 0) {
      return false;
    }
    // Last element in the array is what player act on; thus everything else should stay
    auto newDiscardPile = std::vector<Card>();
    newDiscardPile.emplace_back(this->mDiscardPile[this->mDiscardPile.size() - 1]);

    for (int i = 0; i < this->mDiscardPile.size() - 1; i++) {
      this->mDrawPile.emplace_back(this->mDiscardPile[i]);
    }
    this->ShuffleCards();
    return true;
  }
};
