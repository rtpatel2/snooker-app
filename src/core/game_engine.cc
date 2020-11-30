/**
 * Created by Rishi Patel on 11/28/2020.
 */

#include "core/game_engine.h"
#include "core/table.h"

namespace snooker {

GameEngine::GameEngine(Table* table)
    : table_(table), current_player(&player1_) {}

void GameEngine::AssessTable() {
  for (const Ball& ball : table_->GetBalls()) {
    for (const Pocket& pocket : table_->GetPockets()) {
      if (pocket.DetermineIfPocketed(ball)) {
        current_player->AddBallsPottedLastStroke(const_cast<Ball*>(&ball));
      }
    }
  }

  bool is_red_on = current_player->IsBallOnRed(*table_);
  bool is_stroke_legal = current_player->IsStrokeLegal(
      is_red_on, table_->GetBalls().back().GetFirstContacted(), *table_);

  if (is_stroke_legal) {
    for (Ball* ball : current_player->GetBallsPottedLastStroke()) {
       if (table_->GetRedBallCount() > 0 &&
                 ball->GetColor() != Table::kRed) {
        ball->RespotBall();
      } else {
        table_->RemoveBallFromTable(ball);
      }
    }
  } else {
    for (Ball* ball : current_player->GetBallsPottedLastStroke()) {
      if (ball->GetColor() != Table::kRed) {
        ball->RespotBall();
      } else if (ball->GetColor() == Table::kRed) {
        table_->RemoveBallFromTable(ball);
      }
    }
  }

  if (is_stroke_legal && !current_player->GetBallsPottedLastStroke().empty()) {
    current_player->EndStroke(true);
  } else {
    current_player->EndStroke(false);
    if (current_player ==  &player1_) {
      current_player = &player2_;
    } else {
      current_player = &player1_;
    }
  }
  table_->ResetFirstContacted();
}

}  // namespace snooker