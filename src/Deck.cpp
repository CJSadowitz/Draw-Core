#include "Deck.hpp"
#include <optional>
#include <spdlog/spdlog.h>

namespace game {
  Deck::Deck(std::vector<Card> cards) {
    this->mCards = cards;
  }

  std::optional<std::vector<Card>> Deck::DrawCards(int count) { 
    if (this->mCards.size() == 0 || count == 0) {
      spdlog::warn("[Deck] [DrawCards] No Cards");
      return std::nullopt;
    }

    std::vector<Card> drawnCards = std::vector<Card>();
    for (int i = 0 ; i < count; i++) {
      auto card = this->mCards.back();
      drawnCards.emplace_back(card);
      this->mCards.pop_back();
    }
    return drawnCards;
  }

  void Deck::AddCards(std::vector<Card> cards) {
    for (const auto& card : cards) {
      this->mCards.emplace_back(card);
    }
  }

  std::optional<Card> Deck::PlayCard(Card card) {
    if (!this->HasCard(card)) {
      return std::nullopt;
    }
    this->mCards.pop_back();
    return card;
  }

  bool Deck::HasCard(Card card) {
    if (this->mCards.size() == 0) {
      return false;
    }
    return this->mCards.back() == card;
  }
};
