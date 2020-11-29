/**
 * Created by Rishi Patel on 11/28/2020.
 */

#include "core/player.h"
#include "core/table.h"

namespace snooker {

Player::Player() : last_ball_potted_(nullptr) {}

bool Player::IsBallOnRed() {
  if (last_ball_potted_ == nullptr ||
      last_ball_potted_->GetColor() != Table::kRed) {
    return true;
  } else {
    return false;
  }
}

}  // namespace snooker