#ifndef GAME_ENGINE_HPP
#define GAME_ENGINE_HPP

#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"

namespace game {
  enum TurnDirection {
    FORWARD,
    BACKWARD
  };
  enum MoveType {
    DRAW,
    PLAY_CARD,
    CHOOSE_COLOR,
    RESIGN
  };
  struct Move {
    MoveType type;
    std::optional<Card> card;
  };
  class DrawCore {
    public:
      /**
       * @brief
       */
      DrawCore(unsigned int seed, size_t playerCount, std::vector<Card> cards = std::vector<Card>());

      /**
       * @brief Deals cards one at a time after shuffling until draw pile min is reached
       *
       * @param minimumDeckSize A uint value that describes the lowest the draw pile can reached
       * @return fails with no cards or no players
       */
      bool DealCards(unsigned int minimumDeckSize);

      /**
       * @brief 
       */
      bool MakeMove(Move playerMove);

      /**
       *
       */
      void AddPlayer(Player player);

      /**
       *
       */
      void SetDrawPile(std::vector<Card> cards);

      /**
       *
       */
      void GenerateGame();

      std::optional<std::vector<Player>> GetPlayers() {
        if (this->mPlayers.size() > 0) {
          return this->mPlayers;
        }
        return std::nullopt;
      }

      Deck GetDeck() {
        return this->mDeck;
      }

      std::optional<std::vector<int>> GetWinners() {
        return this->mWinners;
      }

      std::optional<std::vector<int>> GetLosers() {
        return this->mLosers;
      }

    private:
      /**
       * @brief helper function for MakeMove: gets the drawn cards and adds it to player hand
       *
       * @return false if drawing results in game lose or active player dne
       */
      bool PlayDraw();

      /**
       * @brief helper function for MakeMove: places a card on discard
       *
       * @param card the card that was passed in from the move struct
       * @return false if the card is not within the active player's hand or doesn't match the top of the discard
       */
      bool PlayCard(Card card);

      /**
       * @brief checks to see if the card played is a card the active player is allowed to play
       *
       * @param card passes card to player.HasCard() to check validity
       * @return false if no active players or active player does not have that card
       */
      bool IsLegalCard(Card card);

      /**
       * @brief loops through the player list and returns the first (and only) active player
       *
       * @return nullopt when all players are in inactive state
       */
      std::optional<Player> GetActivePlayer();

      /**
       *  @brief when a player resigns, loses, or wins, they are removed from the game loop
       */
      void RemovePlayer();

      Deck mDeck;
      bool mStacking = false;
      int mStackCount = 0;
      TurnDirection mDirection = FORWARD;
      std::vector<Player> mPlayers;
      std::vector<int> mWinners = std::vector<int>();
      std::vector<int> mLosers  = std::vector<int>();
  };

};

#endif

