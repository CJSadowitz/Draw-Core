#include "Deck.hpp"

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

  std::vector<Card> Deck::DrawCards() {}

};
