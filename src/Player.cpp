#include "Player.hpp"
#include <optional>
#include <spdlog/spdlog.h>

namespace game {
  Player::Player(Deck cards, int id) {
    this->mId = id;
    this->AddCards(cards.GetCards());
  }

  void Player::AddCards(std::vector<Card> cards) {
    for (auto card : cards) {
      switch(card.GetType()) {
        case(CardType::RED):
          this->mRedCards.AddCards(card);
          continue;
        case(CardType::GREEN):
          this->mGreenCards.AddCards(card);
          continue;
        case(CardType::BLUE):
          this->mBlueCards.AddCards(card);
          continue;
        case(CardType::YELLOW):
          this->mYellowCards.AddCards(card);
          continue;
        case(CardType::WILD):
          this->mWildCards.AddCards(card);
          continue;
      }
    }
  }

  std::optional<Card> Player::PlayCard(Card pCard) {
    spdlog::info("[Player] [PlayCard] {} played: {}", this->mId, pCard.Print());
    switch (pCard.GetType()) {
      case(CardType::RED):
        return this->mRedCards.PlayCard(pCard);
      case(CardType::GREEN):
        return this->mGreenCards.PlayCard(pCard);
      case(CardType::BLUE):
        return this->mBlueCards.PlayCard(pCard);
      case(CardType::YELLOW):
        return this->mYellowCards.PlayCard(pCard);
      case(CardType::WILD):
        return this->mWildCards.PlayCard(pCard);
    }
    return std::nullopt;
  }

  Deck Player::GetCards(CardType type) {
    switch(type) {
      case(CardType::RED):
        return this->mRedCards;
      case(CardType::GREEN):
        return this->mGreenCards;
      case(CardType::BLUE):
        return this->mBlueCards;
      case(CardType::YELLOW):
        return this->mYellowCards;
      case(CardType::WILD):
        return this->mWildCards;
    }
    return Deck();
  }

  void Player::AddCards(Card card) {
    auto cards = std::vector<Card>();
    cards.emplace_back(card);
    this->AddCards(cards);
  }

  bool Player::HasCard(Card card) {
    auto cards = this->GetCards(card.GetType()).GetCards();
    if (cards.size() == 0) {
      return false;
    }
    auto topCard = cards.back();
    if (topCard == card) {
      return true;
    }
    spdlog::warn("[Player] [HasCard] Id: {}: {}, does not match {}", (int)this->mId, card.Print(), topCard.Print());
    return false;
  }

};
