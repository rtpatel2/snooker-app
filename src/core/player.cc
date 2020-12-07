/**
 * Created by Rishi Patel on 11/28/2020.
 */

#include "core/player.h"
#include "core/table.h"
#include "cinder/gl/gl.h"

#include <vector>

namespace snooker {

Player::Player(bool is_cpu) : is_cpu_(is_cpu), stroke_number_(0), score_(0) {}

bool Player::IsBallOnRed(size_t red_ball_count) const {
  if (red_ball_count > 0 && stroke_number_ % 2 == 0) {
    return true;
  } else {
    return false;
  }
}

bool Player::IsStrokeLegal(size_t red_ball_count,
                           const ci::Color& least_value_color,
                           const ci::Color& cue_first_contacted_color) const {
  bool is_red_on = IsBallOnRed(red_ball_count);
  if (cue_first_contacted_color == Ball::kNoContactColor) {
    return false;
  } else if (is_red_on) {
    return IsStrokeLegalRedOn(cue_first_contacted_color);
  } else {
    return IsStrokeLegalColorsOn(red_ball_count, least_value_color,
                                 cue_first_contacted_color);
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

bool Player::GetIsCPU() const {
  return is_cpu_;
}

const std::vector<Ball>& Player::GetBallsPottedLastStroke() const {
  return balls_potted_last_stroke_;
}

size_t Player::GetStrokeNumber() const {
  return stroke_number_;
}

size_t Player::GetScore() const {
  return score_;
}

bool Player::IsStrokeLegalRedOn(
    const ci::Color& cue_first_contacted_color) const {
  if (cue_first_contacted_color != Ball::kRed) {
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

bool Player::IsStrokeLegalColorsOn(
    size_t red_ball_count, const ci::Color& least_value_color,
    const ci::Color& cue_first_contacted_color) const {
  if (balls_potted_last_stroke_.size() > 1) {
    return false;
  } else if (!balls_potted_last_stroke_.empty() &&
             (balls_potted_last_stroke_.front().GetColor() !=
                  cue_first_contacted_color ||
              balls_potted_last_stroke_.front().GetColor() == Ball::kWhite)) {
    return false;
  } else if (red_ball_count != 0 && cue_first_contacted_color == Ball::kRed) {
    return false;
  } else if (red_ball_count == 0 &&
             cue_first_contacted_color != least_value_color) {
    return false;
  } else {
    return true;
  }
}

}  // namespace snooker