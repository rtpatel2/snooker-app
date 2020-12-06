/**
 * Created by Rishi Patel on 11/28/2020.
 */

#include "core/player.h"
#include "core/table.h"
#include "cinder/gl/gl.h"

#include <vector>

namespace snooker {

Player::Player() : stroke_number_(0), score_(0) {}

bool Player::IsBallOnRed(const Table& table) const {
  if (table.GetRedBallCount() != 0 && stroke_number_ % 2 == 0) {
    return true;
  } else {
    return false;
  }
}

bool Player::IsStrokeLegal(const Table& table) const {
  ci::Color cue_color_first_contacted = table.GetBalls().back()
                                             .GetFirstContacted();
  bool is_red_on = IsBallOnRed(table);
  if (cue_color_first_contacted == Ball::kNoContactColor) {
    return false;
  } else if (is_red_on) {
    return IsStrokeLegalRedOn(cue_color_first_contacted, table);
  } else {
    return IsStrokeLegalColorsOn(cue_color_first_contacted, table);
  }
}

void Player::AddBallsPottedLastStroke(const Ball& ball) {
  balls_potted_last_stroke_.push_back(ball);
}

void Player::EndStroke(bool still_at_table) {
  if (still_at_table) {
    ++stroke_number_;
  } else {
    stroke_number_ = 0;
  }
  balls_potted_last_stroke_.clear();
}

void Player::AddPoints(size_t points_to_add) {
  score_ += points_to_add;
}

const std::vector<Ball>& Player::GetBallsPottedLastStroke() const {
  return balls_potted_last_stroke_;
}

size_t Player::GetStrokeNumber() const {
  return stroke_number_;
}

bool Player::IsStrokeLegalRedOn(const ci::Color& cue_color_first_contacted,
                        const Table& table) const {
  if (cue_color_first_contacted != Ball::kRed) {
    return false;
  }
  for (const Ball& ball : balls_potted_last_stroke_) {
    ci::Color color = ball.GetColor();
    if (color == Ball::kWhite) {
      return false;
    } else if (color != Ball::kRed) {
      return false;
    }
  }
  return true;
}

bool Player::IsStrokeLegalColorsOn(const ci::Color& cue_color_first_contacted,
                           const Table& table) const {
  if (balls_potted_last_stroke_.size() > 1) {
    return false;
  } else if (!balls_potted_last_stroke_.empty() &&
      (balls_potted_last_stroke_.front().GetColor() !=
       cue_color_first_contacted ||
       balls_potted_last_stroke_.front().GetColor() == Ball::kWhite)) {
    return false;
  } else if (table.GetRedBallCount() != 0 &&
      cue_color_first_contacted == Ball::kRed) {
    return false;
  } else if (table.GetRedBallCount() == 0 &&
      cue_color_first_contacted != table.FindLeastPointValueColor()) {
    return false;
  } else {
    return true;
  }
}

}  // namespace snooker