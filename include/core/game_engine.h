/**
 * Created by Rishi Patel on 11/28/2020.
 */

#pragma once

#include "table.h"
#include "cue.h"

namespace snooker {

/** Maintains game logic and control flow of a game of snooker. */
class GameEngine {
 public:
  GameEngine(Table* table, Cue* cue);

  void AssessTable();

 private:
  Table* table_;
  Cue* cue_;
};

}  // namespace snooker