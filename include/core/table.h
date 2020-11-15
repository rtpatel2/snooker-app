/**
 * Created by Rishi Patel on 11/15/2020.
 */

#pragma once

#include "ball.h"
#include "table_component.h"
#include "cinder/gl/gl.h"

#include <vector>

namespace snooker {

/** Maintains functionality of a snooker table. */
class Table {
 public:
  /**
   * Creates a new Table with the specified TableComponents.
   *
   * @param components components of the Table edge.
   */
  explicit Table(const std::vector<TableComponent>& components);

  /**
   * Adds the specified Ball to this Table if the Ball is within the Table's
   * bounds.
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

  //TODO: Sort out what to do with this
  const ci::Rectf& GetWalls() const;
  const std::vector<Ball>& GetBalls() const;

 private:
  std::vector<TableComponent> components_;
  ci::Rectf walls_;
  std::vector<Ball> balls_;
};

}  // namespace snooker