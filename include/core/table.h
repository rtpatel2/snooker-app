/**
 * Created by Rishi Patel on 11/15/2020.
 */

#pragma once

#include <vector>

#include "ball.h"
#include "cinder/gl/gl.h"
#include "table_cushion.h"

namespace snooker {

/** Maintains functionality of a snooker table. */
class Table {
 public:
  Table();

  /**
   * Creates a new Table with the specified TableCushions.
   *
   * @param walls walls of the Table.
   * @param cushions cushions of the Table edge.
   */
  Table(const ci::Rectf& walls,
        const std::vector<TableCushion*>& cushions);

  /**
   * Adds the specified Ball to this Table if the Ball is within the Table's
   * bounds.
   *
   * @param ball Ball to add.
   */
  void AddBall(const Ball& ball);

  /**
   * Adds the specified TableCushion to this Table.
   *
   * @param cushion TableCushion to add.
   */
  void AddCushion(TableCushion* cushion);

  /**
   * Updates the velocities and positions of all Balls, simulating the
   * passage of one unit of time.
   */
  void IncrementTime();

  /** Removes all Balls from this Table. */
  void ClearTable();

  const std::vector<TableCushion*>& GetCushions() const;
  const ci::Rectf& GetWalls() const;
  const std::vector<Ball>& GetBalls() const;

 private:
  std::vector<TableCushion*> cushions_;
  ci::Rectf walls_;
  std::vector<Ball> balls_;
};

}  // namespace snooker