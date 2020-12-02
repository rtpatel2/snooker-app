/**
 * Created by Rishi Patel on 11/28/2020.
 */

#include "core/game_engine.h"
#include "core/ball.h"
#include "core/table.h"

namespace snooker {

GameEngine::GameEngine(Table* table)
    : table_(table),
      current_player_(&player1_),
      stroke_started_(false),
      cue_pull_back_(0),
      stroke_completed_(false) {}

void GameEngine::PocketBalls() {
  for (const Ball& ball : table_->GetBalls()) {
    for (const Pocket& pocket : table_->GetPockets()) {
      if (pocket.DetermineIfPocketed(ball)) {
        current_player_->AddBallsPottedLastStroke(ball);
        break;
      }
    }
  }

  for (const Ball& ball : current_player_->GetBallsPottedLastStroke()) {
    table_->RemoveBallFromTable(ball);
  }

  EndStroke();
}

void GameEngine::EndStroke() {
  if (table_->IsSteady() && stroke_completed_) {
    bool is_stroke_legal = current_player_->IsStrokeLegal(*table_);

    for (const Ball& ball : current_player_->GetBallsPottedLastStroke()) {
      if ((is_stroke_legal && table_->GetRedBallCount() > 0 &&
           ball.GetColor() != Ball::kRed) ||
          (!is_stroke_legal && ball.GetColor() != Ball::kRed)) {
        //TODO: Create copy function
        Ball ball_copy(ball.GetInitialPosition(), glm::vec2(0, 0),
                       ball.GetColor(), ball.GetRadius(), ball.GetMass(),
                       ball.GetPointValue());
        table_->AddBall(ball_copy);
      }
    }

    if (is_stroke_legal &&
        !current_player_->GetBallsPottedLastStroke().empty()) {
      current_player_->EndStroke(true);
    } else {
      current_player_->EndStroke(false);
      if (current_player_ == &player1_) {
        current_player_ = &player2_;
      } else {
        current_player_ = &player1_;
      }
    }
    stroke_completed_ = false;
    table_->ResetFirstContacted();
  }
}

void GameEngine::HandleStrokeStart(const glm::vec2& start_position) {
  if (table_->IsSteady()) {
    stroke_started_ = true;
    stroke_start_ = start_position;
  }
}

void GameEngine::HandleCuePullBack(const glm::vec2& mouse_position) {
  if (stroke_started_) {
    cue_pull_back_ =
        std::fminf(Table::kMaxPullBack, glm::length(mouse_position -
                                                stroke_start_));
  }
}

void GameEngine::HandleStrokeEnd(const glm::vec2& end_position) {
  if (table_->IsSteady() && stroke_started_) {
    glm::vec2 velocity(stroke_start_ - end_position);
    if (glm::length(velocity) == 0) {
      table_->SetCueBallVelocity(glm::vec2(0, 0));
    } else {
      float speed = std::fminf(Table::kMaxPullBack, glm::length(velocity));
      table_->SetCueBallVelocity(glm::normalize(velocity) * speed *
                         Table::kScalingFactor * Ball::kTimeScaleFactor *
                         Table::kCueStrokeFactor);
    }
    stroke_started_ = false;
    cue_pull_back_ = 0;
    stroke_completed_ = true;
  }
}

float GameEngine::ComputeCueAngle(const glm::vec2& mouse_position) const {
  glm::vec2 cue_vector = table_->GetBalls().back().GetPosition() - mouse_position;
  float cue_angle = glm::atan(cue_vector.y / cue_vector.x);
  cue_angle += (cue_vector.x < 0) ? static_cast<float>(M_PI) : 0;
  return cue_angle;
}

ci::Rectf GameEngine::ComputeCueDimensions() const {
  return ci::Rectf(-Table::kCueLength - cue_pull_back_, -Table::kCueWidth,
                   -Table::kBallRadius - cue_pull_back_, Table::kCueWidth);
}

bool GameEngine::IsPlayer1Turn() const {
  if (current_player_ == &player1_) {
    return true;
  } else {
    return false;
  }
}

const Player& GameEngine::GetPlayer1() const {
  return player1_;
}

const Player& GameEngine::GetPlayer2() const {
  return player2_;
}

const Player* GameEngine::GetCurrentPlayer() const {
  return current_player_;
}

bool GameEngine::GetStrokeStarted() const {
  return stroke_started_;
}

const glm::vec2& GameEngine::GetStrokeStart() const {
  return stroke_start_;
}

float GameEngine::GetCuePullBack() const {
  return cue_pull_back_;
}

bool GameEngine::GetStrokeCompleted() const {
  return stroke_completed_;
}

}  // namespace snooker