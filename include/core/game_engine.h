/**
 * Created by Rishi Patel on 11/28/2020.
 */

#pragma once

#include "table.h"
#include "player.h"

namespace snooker {

/** Maintains game logic and control flow of a game of snooker. */
class GameEngine {
 public:
  GameEngine(Table* table);

  /** Assesses the state of the Table. */
  void AssessTable();

  /**
   * Determines whether or not Player 1 is currently at the Table.
   *
   * @return true if Player 1 is at the table, and false otherwise.
   */
  bool IsPlayer1Turn() const;

 private:
  Table* table_;
  Player player1_;
  Player player2_;
  Player* current_player;
};

}  // namespace snooker