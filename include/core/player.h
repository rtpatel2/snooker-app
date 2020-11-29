/**
 * Created by Rishi Patel on 11/28/2020.
 */

#pragma once

#include "ball.h"
#include "table.h"
#include "cinder/gl/gl.h"

#include <vector>

namespace snooker {

/** Maintains game logic and control flow of a game of snooker. */
class Player {
 public:
  Player();

  /**
   * Determines whether or not the "ball-on" for this Player is red (i.e.,
   * whether or not the next ball the Player must contact and pot is red)
   *
   * @param table the current state of the Table.
   * @return true if the "ball-on" is red, and false otherwise.
   */
  bool IsBallOnRed(const Table& table);

  /**
   * Determines whether or not the previous stroke was legal.
   *
   * @param red_on true if red is the ball-on, and false otherwise.
   * @param cue_color_first_contacted the color that the cue ball first
   * contacted on this stroke.
   * @param red_ball_count number of red balls on the Table.
   * @return true if the stroke was legal, and false otherwise.
   */
  bool IsStrokeLegal(bool red_on, const ci::Color& cue_color_first_contacted,
                     size_t red_ball_count);

 private:
  std::vector<ci::Color> colors_potted_last_stroke_;
  size_t stroke_number_;

};

}  // namespace snooker