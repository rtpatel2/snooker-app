/**
 * Created by Rishi Patel on 11/28/2020.
 */

#include "core/player.h"
#include "core/table.h"
#include "cinder/gl/gl.h"

#include <vector>

namespace snooker {

Player::Player() : stroke_number_(0) {}

bool Player::IsBallOnRed(const Table& table) {
  if (table.GetRedBallCount() != 0 && stroke_number_ % 2 == 0) {
    return true;
  } else {
    return false;
  }
}

bool Player::IsStrokeLegal(bool red_on,
                           const ci::Color& cue_color_first_contacted,
                           const Table& table) {
  if (red_on) {
    for (const ci::Color& color : colors_potted_last_stroke_) {
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
    if (colors_potted_last_stroke_.size() > 1) {
      return false;
    }
    if (!colors_potted_last_stroke_.empty() &&
        (colors_potted_last_stroke_.front() != cue_color_first_contacted ||
        colors_potted_last_stroke_.front() == Table::kWhite)) {
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

}  // namespace snooker