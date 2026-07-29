#include "DrawEngine.hpp"
#include <cstdlib>
#include <cstring>

namespace game {
  Deck::Deck(Card* cards, size_t size, unsigned int seed) {
    // May have to move this to Engine class
    this->mSeed.seed(seed);

    this->mDrawPile = (Card*) std::malloc(size * sizeof(Card));
    std::memcpy(this->mDrawPile, cards, size);
    this->mDrawPileSize = size;
  }

  Deck::~Deck() {
    free(this->mDrawPile);
    free(this->mDiscardPile);
  }

  void Deck::ShuffleCards() {
    Card* drawPile = (Card*) std::malloc(this->mDrawPileSize * sizeof(Card));
    std::memcpy(drawPile, this->mDrawPile, this->mDrawPileSize);
    Card* shuffledCards = (Card*) std::malloc(this->mDrawPileSize * sizeof(Card));
    if (shuffledCards == nullptr) {
      // Think about logging and exiting...
      exit(EXIT_FAILURE);
    }

    unsigned int remainingCards = this->mDrawPileSize;
    for (int i = 0; i < remainingCards; i++) {
      std::uniform_int_distribution<int> distr(0, i);
      int index = distr(this->mSeed);
      shuffledCards[i] = drawPile[index];
      for (int j = index; j < remainingCards - 1; j++) {
        drawPile[j] = drawPile[j + 1];
      }
      remainingCards--;
    }

    std::memcpy(this->mDrawPile, shuffledCards, this->mDrawPileSize);
    free(shuffledCards);
    free(drawPile);
  }

};
