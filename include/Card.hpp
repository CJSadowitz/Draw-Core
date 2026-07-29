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

  struct Card {
    CardType type;
    CardValue value;
  };
};

#endif
