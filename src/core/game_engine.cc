/**
 * Created by Rishi Patel on 11/28/2020.
 */

#include "core/game_engine.h"
#include "core/table.h"
#include "core/cue.h"

namespace snooker {

GameEngine::GameEngine(Table* table, Cue* cue)
    : table_(table), cue_(cue) {}

void GameEngine::AssessBoard() {
  if (table_ != nullptr &&
      table_->GetBalls().back().GetFirstContacted() != nullptr &&
      table_->GetBalls().back().GetFirstContacted()->GetColor() !=
          table_->kRed) {

  }
}

}  // namespace snooker