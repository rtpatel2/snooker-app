/**
 * Created by Rishi Patel on 11/15/2020.
 */

#pragma once

#include "core/ball.h"
#include "cinder/gl/gl.h"

namespace snooker {

/** Maintains functionality of a single component of a snooker table. */
class TableComponent {
 public:
  /**
   * Creates a new TableComponent.
   *
   * @param position position of this TableComponent.
   */
  TableComponent(const glm::vec2& position);

 private:
  glm::vec2 position_;
};

/** Maintains functionality of a straight edge of the snooker table. */
class StraightEdge : public TableComponent {
 public:
  /**
   * Computes the velocity of a Ball after collision with a straight edge of
   * a table.
   * 
   * @param ball snooker Ball colliding with table.
   * @return velocity of the Ball after collision.
   */
  glm::vec2 ComputeVelocityAfterCollision(const Ball& ball);
};

}  // namespace snooker