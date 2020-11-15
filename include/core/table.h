/**
 * Created by Rishi Patel on 11/15/2020.
 */

#pragma once

#include "ball.h"
#include "cinder/gl/gl.h"

#include <vector>

namespace snooker {

/** Maintains functionality of a snooker table. */
class Table {
 public:
  /**
   * Creates a new Table with the specified rectangular walls.
   *
   * @param walls Cinder rectangle specifying the walls of the Table.
   */
  Table(const ci::Rectf& walls);

  /**
   * Adds the specified Ball to this Table if the Ball is within the Table's
   * walls.
   *
   * @param ball ball to add.
   */
  void AddBall(const Ball& ball);

  /**
   * Updates the velocities and positions of all Balls, simulating the
   * passage of one unit of time.
   */
  void IncrementTime();

  /** Removes all Balls from this Table. */
  void ClearTable();

 private:
  ci::Rectf walls_;
  std::vector<Ball> balls_;
};

}  // namespace snooker