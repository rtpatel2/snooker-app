/**
 * Created by Rishi Patel on 11/28/2020.
 */

#pragma once

#include "cinder/gl/gl.h"

namespace snooker {

/** Maintains game logic and control flow of a game of snooker. */
class Player {
 public:
  Player();

  ci::Color DetermineNextToContact();

 private:
  ci::Color last_color_potted_;

};

}  // namespace snooker