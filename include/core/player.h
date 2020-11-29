/**
 * Created by Rishi Patel on 11/28/2020.
 */

#pragma once

#include "core/ball.h"
#include "cinder/gl/gl.h"

namespace snooker {

/** Maintains game logic and control flow of a game of snooker. */
class Player {
 public:
  Player();

  /**
   * Determines whether or not the "ball-on" for this Player is red (i.e.,
   * whether or not the next ball the Player must contact and pot is red)
   *
   * @return true if the "ball-on" is red, and false otherwise.
   */
  bool IsBallOnRed();

 private:
  Ball* last_ball_potted_;

};

}  // namespace snooker