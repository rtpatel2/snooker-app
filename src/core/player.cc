/**
 * Created by Rishi Patel on 11/28/2020.
 */

#include "core/player.h"
#include "core/table.h"
#include "cinder/gl/gl.h"

#include <vector>

namespace snooker {

Player::Player() : stroke_number_(0) {}

//TODO: Make private if possible
bool Player::IsBallOnRed(const Table& table) const {
  if (table.GetRedBallCount() != 0 && stroke_number_ % 2 == 0) {
    return true;
  } else {
    return false;
  }
}

bool Player::IsStrokeLegal(bool is_red_on,
                           const ci::Color& cue_color_first_contacted,
                           const Table& table) const {
  if (is_red_on) {
    for (Ball* ball : balls_potted_last_stroke_) {
      ci::Color color = ball->GetColor();
      if (color == Table::kWhite) {
        return false;
      }
      if (cue_color_first_contacted != Table::kRed) {
        return false;
      }
      if (color != Table::kRed) {
        return false;
      }
    }
  } else {
    if (balls_potted_last_stroke_.size() > 1) {
      return false;
    }
    if (!balls_potted_last_stroke_.empty() &&
        (balls_potted_last_stroke_.front()->GetColor() !=
             cue_color_first_contacted ||
         balls_potted_last_stroke_.front()->GetColor() == Table::kWhite)) {
      return false;
    }
    if (table.GetRedBallCount() != 0 &&
        cue_color_first_contacted == Table::kRed) {
      return false;
    }
    if (table.GetRedBallCount() == 0 &&
        cue_color_first_contacted != table.DetermineLeastPointsColor()) {
      return false;
    }
  }

  return true;
}

void Player::AddBallsPottedLastStroke(Ball* ball) {
  balls_potted_last_stroke_.push_back(ball);
}

void Player::ClearBallsPottedLastStroke() {
  balls_potted_last_stroke_.clear();
}

const std::vector<Ball*>& Player::GetBallsPottedLastStroke() const {
  return balls_potted_last_stroke_;
}

}  // namespace snooker