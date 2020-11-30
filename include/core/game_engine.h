/**
 * Created by Rishi Patel on 11/28/2020.
 */

#pragma once

#include "table.h"
#include "cue.h"
#include "player.h"

namespace snooker {

/** Maintains game logic and control flow of a game of snooker. */
class GameEngine {
 public:
  GameEngine(Table* table);

  /** Runs a game of snooker. */
  void RunGame();

  /**
   * Assesses the state of the Table.
   *
   * @param player Player who just stroked.
   */
  void AssessTable(Player* player);

 private:
  Table* table_;
  Player player1_;
  Player player2_;
  Player* next_to_stroke_;
};

}  // namespace snooker