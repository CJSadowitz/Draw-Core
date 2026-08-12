#ifndef CARD_HPP
#define CARD_HPP

namespace game {
  enum CardType {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WILD
  };

  enum CardValue {
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
    CHANGE_COLOR_RED,
    CHANGE_COLOR_GREEN,
    CHANGE_COLOR_BLUE,
    CHANGE_COLOR_YELLOW,
    CHANGE_COLOR_PLUS_FOUR
  };

  struct Card {
    CardType type;
    CardValue value;
  };
};

#endif
