#ifndef CARD_HPP
#define CARD_HPP

#include <magic_enum/magic_enum.hpp>
#include <spdlog/spdlog.h>

namespace game {
  enum class CardType {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WILD
  };

  enum class CardValue {
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    SKIP,
    PLUS_TWO,
    REVERSE,
    CHANGE_COLOR,
    CHANGE_COLOR_PLUS_FOUR
  };

  class Card {
    public:
      Card(CardType type, CardValue value) {
        this->type = type;
        this->value = value;
      }

      void ChangeColor(CardType type) {
        if (this->type == CardType::WILD) {
          spdlog::info("[Card] [ChangeColor] {} to {}", magic_enum::enum_name(this->type), magic_enum::enum_name(type));
          switch (type) {
            case(CardType::RED):
              this->type = CardType::RED;
              break;
            case(CardType::GREEN):
              this->type = CardType::GREEN;
              break;
            case(CardType::BLUE):
              this->type = CardType::BLUE;
              break;
            case(CardType::YELLOW):
              this->type = CardType::YELLOW;
              break;
            case(CardType::WILD):
              break;
          }
        }
      }

      std::string Print() {
        return (std::string)magic_enum::enum_name(this->type) + ' '  + (std::string)magic_enum::enum_name(this->value);
      }

      void Reset() {
        // Is this card actually a wild?
        if (this->value == CardValue::CHANGE_COLOR || this->value == CardValue::CHANGE_COLOR_PLUS_FOUR) {
          spdlog::info("[Card] [Reset] {} to {}", magic_enum::enum_name(this->type), magic_enum::enum_name(CardType::WILD));
          this->type = CardType::WILD;
        }
      }

      CardType GetType() const { return this->type; }

      CardValue GetValue() const { return this->value; }

      bool operator==(const Card& other) {
        return (this->type == other.GetType() && this->value == other.GetValue());
      }

      bool operator!=(const Card& other) {
        return (this->type != other.GetType() || this->value != other.GetValue());
      }

    private:
    CardType type;
    CardValue value;
  };
};

#endif
