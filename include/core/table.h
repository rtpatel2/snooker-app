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
  Table();

  /**
   * Creates a new Table with the specified TableComponents.
   *
   * @param walls walls of the Table.
   * @param components components of the Table edge.
   */
  Table(const ci::Rectf& walls,
        const std::vector<TableComponent*>& components);

  /**
   * Adds the specified Ball to this Table if the Ball is within the Table's
   * bounds.
   *
   * @param ball Ball to add.
   */
  void AddBall(const Ball& ball);

  /**
   * Adds the specified TableComponent to this Table.
   *
   * @param component TableComponent to add.
   */
  void AddComponent(TableComponent* component);

  /**
   * Updates the velocities and positions of all Balls, simulating the
   * passage of one unit of time.
   */
  void IncrementTime();

  /** Removes all Balls from this Table. */
  void ClearTable();

  const std::vector<TableComponent*>& GetComponents() const;
  const ci::Rectf& GetWalls() const;
  const std::vector<Ball>& GetBalls() const;

 private:
  std::vector<TableComponent*> components_;
  ci::Rectf walls_;
  std::vector<Ball> balls_;
};

}  // namespace snooker