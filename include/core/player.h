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

  //TODO: Make private if possible
  /**
   * Determines whether or not the "ball-on" for this Player is red (i.e.,
   * whether or not the next ball the Player must contact and pot is red)
   *
   * @param table current state of the Table.
   * @return true if the "ball-on" is red, and false otherwise.
   */
  bool IsBallOnRed(const Table& table) const;

  /**
   * Determines whether or not the previous stroke was legal.
   *
   * @param is_red_on true if red is the ball-on, and false otherwise.
   * @param cue_color_first_contacted the color that the cue ball first
   * contacted on this stroke.
   * @param table current state of the Table.
   * @return true if the stroke was legal, and false otherwise.
   */
  bool IsStrokeLegal(bool is_red_on, const ci::Color& cue_color_first_contacted,
                     const Table& table) const;

  /**
   * Adds any Balls potted by this Player on his/her previous stroke to the
   * maintained list.
   *
   * @param ball pointer to a Ball potted by this Player.
   */
  void AddBallsPottedLastStroke(Ball* ball);

  /** Clears all Balls from the list of Balls potted last stroke. */
  void ClearBallsPottedLastStroke();

  const std::vector<Ball*>& GetBallsPottedLastStroke() const;

 private:
  std::vector<Ball*> balls_potted_last_stroke_;
  size_t stroke_number_;
  size_t score_;
};

}  // namespace snooker