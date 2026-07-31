#include "Player.hpp"
#include <optional>

namespace game {
  Player::Player(std::vector<Card> cards) {
    this->AddCards(cards);
  }

  bool Player::AddCards(std::vector<Card> cards) {
    if (cards.size() == 0) {
      return false;
    }
    for (auto card : cards) {
      this->AddCard(card);
    }
    return true;
  }

  std::optional<Card> Player::PlayCard(CardType type) {
    std::optional<Card> card = std::nullopt;
    switch (type) {
      case(CardType::RED):
        if (this->mRedCards.size() > 0) {
          card = this->mRedCards.back();
          this->mRedCards.pop_back();
        }
        break;
      case(CardType::GREEN):
        if (this->mGreenCards.size() > 0) {
          card = mGreenCards.back();
          this->mGreenCards.pop_back();
        }
        break;
      case(CardType::BLUE):
        if (this->mBlueCards.size() > 0) {
          card = this->mBlueCards.back();
          this->mBlueCards.pop_back();
        }
        break;
      case(CardType::YELLOW):
        if (this->mYellowCards.size() > 0) {
          card = this->mYellowCards.back();
          this->mYellowCards.pop_back();
        }
        break;
      case(CardType::WILD):
        if (this->mWildCards.size() > 0) {
          card = this->mWildCards.back();
          this->mWildCards.pop_back();
        }
        break;
    }
    // Reconstruct mCards cannot remove single instance due to index being unknown and possible duplicates
    if (card != std::nullopt) {
      this->mCards = std::vector<Card>();
      // Has to be a better way to do this
      for (auto rCard : this->mRedCards)    { this->mCards.emplace_back(rCard); }
      for (auto gCard : this->mGreenCards)  { this->mCards.emplace_back(gCard); }
      for (auto bCard : this->mBlueCards)   { this->mCards.emplace_back(bCard); }
      for (auto yCard : this->mYellowCards) { this->mCards.emplace_back(yCard); }
      for (auto wCard : this->mWildCards)   { this->mCards.emplace_back(wCard); }
    }
    return card;
  }

  std::optional<std::vector<Card>> Player::GetCards(CardType type) {
    switch(type) {
      case(CardType::RED):
        if (this->mRedCards.size() > 1) {
          return this->mRedCards;
        }
        break;
      case(CardType::GREEN):
        if (this->mGreenCards.size() > 1) {
          return this->mGreenCards;
        }
        break;
      case(CardType::BLUE):
        if (this->mBlueCards.size() > 1) {
          return this->mBlueCards;
        }
        break;
      case(CardType::YELLOW):
        if (this->mYellowCards.size() > 1) {
          return this->mYellowCards;
        }
        break;
      case(CardType::WILD):
        if (this->mWildCards.size() > 1) {
          return this->mWildCards;
        }
        break;
    }
    return std::nullopt;
  }

  std::optional<std::vector<Card>> Player::GetCards() {
    if (this->mCards.size() > 0) {
      return this->mCards;
    }
    return std::nullopt;
  }

  void Player::AddCard(Card card) {
    switch(card.type) {
      case(CardType::RED):
        this->mRedCards.emplace_back(card);
        break;
      case(CardType::GREEN):
        this->mGreenCards.emplace_back(card);
        break;
      case(CardType::BLUE):
        this->mBlueCards.emplace_back(card);
        break;
      case(CardType::YELLOW):
        this->mYellowCards.emplace_back(card);
        break;
      case(CardType::WILD):
        this->mWildCards.emplace_back(card);
        break;
    }
    this->mCards.emplace_back(card);
  }

};

