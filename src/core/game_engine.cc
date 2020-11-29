/**
 * Created by Rishi Patel on 11/28/2020.
 */

#include "core/game_engine.h"
#include "core/table.h"
#include "core/cue.h"

namespace snooker {

GameEngine::GameEngine(Table* table, Cue* cue)
    : table_(table), cue_(cue) {}

void GameEngine::AssessTable() {

  /**
   *  decide which is ball is on for the first stroke:
   *    - if even stroke and reds up, red
   *    - otherwise, color
   *
   *  determine if a foul was committed:
   *    - if red is up, a LEGAL shot must have:
   *        - white not potted
   *        - white first contact w/ red
   *        - only reds potted, multiple ok
   *    - if color is up, a LEGAL shot must have:
   *        -bla bla bla
   *
   *  if it's a foul, other player gets cue
   *
   *  if it's not a foul, then if the current player potted one, then they
   *  keep going; otherwise, other player gets cue
   *
   *  reset all the table things, make sure red count is maintained properly
   */


//  if (table_ != nullptr &&
//      table_->GetBalls().back().GetFirstContacted() != nullptr &&
//      table_->GetBalls().back().GetFirstContacted()->GetColor() !=
//          table_->kRed) {
//
//  }
}

}  // namespace snooker