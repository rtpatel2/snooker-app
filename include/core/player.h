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
  /**
   * Creates a new Player instance.
   *
   * @param is_cpu_controlled true if this Player is controlled by a CPU, and
   * false otherwise.
   */
  explicit Player(bool is_cpu_controlled);

  /**
   * Determines whether or not the "ball-on" for this Player is red (i.e.,
   * whether or not the next ball the Player must contact and pot is red)
   *
   * @param red_ball_count the number of red Balls on the Table.
   * @return true if the "ball-on" is red, and false otherwise.
   */
  bool IsBallOnRed(size_t red_ball_count) const;

  /**
   * Determines whether or not the previous stroke was legal.
   *
   * @param red_ball_count the number of red Balls on the Table.
   * @param least_value_color color with lowest point value on the Table.
   * @param cue_first_contacted_color color first contacted by cue Ball.
   * @return true if the stroke was legal, and false otherwise.
   */
  bool IsStrokeLegal(size_t red_ball_count, const ci::Color& least_value_color,
                     const ci::Color& cue_first_contacted_color) const;

  /**
   * Adds a Ball pocketed by this Player on his/her previous stroke to the
   * maintained list.
   *
   * @param ball Ball potted by this Player.
   */
  void AddBallPocketedLastStroke(const Ball& ball);

  /**
   * Ends the Player's current stroke, updating necessary fields.
   *
   * @param still_at_table true if this Player is still at the Table (i.e.,
   * previous stroke was legal and potted the ball-on), and false otherwise.
   */
  void EndStroke(bool still_at_table);

  /**
   * Adds the specified number of points to this Player's score.
   *
   * @param points_to_add number of points to add.
   */
  void AddPoints(size_t points_to_add);

  bool IsCPUControlled() const;
  const std::vector<Ball>& GetBallsPocketedLastStroke() const;
  size_t GetStrokeNumber() const;
  size_t GetScore() const;

  /** Speed with which CPU pulls back the cue. */
  static constexpr float kCPUPullBackSpeed = 50.0f;

 private:
  /**
   * Determines whether or not the previous stroke was legal, given that the
   * "ball-on" was red.
   *
   * @param cue_first_contacted_color color first contacted by cue Ball.
   * @return true if the stroke was legal, and false otherwise.
   */
  bool IsStrokeLegalRedOn(const ci::Color& cue_first_contacted_color) const;

  /**
   * Determines whether or not the previous stroke was legal, given that the
   * "ball-on" was colored.
   *
   * @param red_ball_count the number of red Balls on the Table.
   * @param least_value_color color with lowest point value on the Table.
   * @param cue_first_contacted_color color first contacted by cue Ball.
   * @return true if the stroke was legal, and false otherwise.
   */
  bool IsStrokeLegalColorsOn(size_t red_ball_count,
                             const ci::Color& least_value_color,
                             const ci::Color& cue_first_contacted_color) const;

  bool is_cpu_controlled_;
  std::vector<Ball> balls_potted_last_stroke_;
  size_t stroke_number_;
  size_t score_;
};

}  // namespace snooker