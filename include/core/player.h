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
  /** Creates a new Player. */
  Player();

  /**
   * Determines whether or not the previous stroke was legal.
   *
   * @param cue_color_first_contacted the color of the Ball that the cue Ball
   * first contacted on this stroke.
   * @param table current state of the Table.
   * @return true if the stroke was legal, and false otherwise.
   */
  bool IsStrokeLegal(const ci::Color& cue_color_first_contacted,
                     const Table& table) const;

  /**
   * Adds any Balls potted by this Player on his/her previous stroke to the
   * maintained list.
   *
   * @param ball Ball potted by this Player.
   */
  void AddBallsPottedLastStroke(const Ball& ball);

  /**
   * Ends the Player's current stroke, updating necessary fields.
   *
   * @param still_at_table true if this Player is still at the Table (i.e.,
   * previous stroke was legal and potted the ball-on), and false otherwise.
   */
  void EndStroke(bool still_at_table);

  const std::vector<Ball>& GetBallsPottedLastStroke() const;

 private:
  /**
   * Determines whether or not the "ball-on" for this Player is red (i.e.,
   * whether or not the next ball the Player must contact and pot is red)
   *
   * @param table current state of the Table.
   * @return true if the "ball-on" is red, and false otherwise.
   */
  bool IsBallOnRed(const Table& table) const;

  /**
   * Determines whether or not the previous stroke was legal, given that the
   * "ball-on" was red.
   *
   * @param cue_color_first_contacted the color of the Ball that the cue Ball
   * first contacted on this stroke.
   * @param table current state of the Table.
   * @return true if the stroke was legal, and false otherwise.
   */
  bool IsStrokeLegalRedOn(const ci::Color& cue_color_first_contacted,
                          const Table& table) const;

  /**
   * Determines whether or not the previous stroke was legal, given that the
   * "ball-on" was colored.
   *
   * @param cue_color_first_contacted the color of the Ball that the cue Ball
   * first contacted on this stroke.
   * @param table current state of the Table.
   * @return true if the stroke was legal, and false otherwise.
   */
  bool IsStrokeLegalColorsOn(const ci::Color& cue_color_first_contacted,
                             const Table& table) const;

  std::vector<Ball> balls_potted_last_stroke_;
  size_t stroke_number_;
  size_t score_;
};

}  // namespace snooker