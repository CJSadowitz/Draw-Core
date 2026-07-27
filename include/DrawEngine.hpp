#include <stdio.h>

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

  class Deck {
    public:
      Deck(Card* cards, size_t size);

      Card* DrawCards();

    private:
      Card* drawPile;
      Card* discardPile;
  };

  class Player {
    public:
      Player(Card* cards, size_t size);

      Card* GetCards(CardType type);

      void AddCard(Card card);

      void RemoveCard(Card card);

    private:
      Card* cards;
  };

  class DrawCore {
    public:
      DrawCore(unsigned int seed);

      void PlayCard(Card card);

      unsigned int GetPlayerTurn();

    private:

      void GenerateGame(size_t playerCount);

      unsigned int seed;
      unsigned int turn;
      Deck* deck;
      Player players[];
  };

};

