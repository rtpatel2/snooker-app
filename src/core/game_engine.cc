/**
 * Created by Rishi Patel on 11/28/2020.
 */

#include "core/game_engine.h"
#include "core/table.h"
#include "core/cue.h"

namespace snooker {

GameEngine::GameEngine(const Table& table, const Cue& cue)
    : table_(table), cue_(cue) {}

void GameEngine::AssessBoard() {

}

}  // namespace snooker