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
   * Creates a new TableComponent with the specified bounds.
   *
   * @param bounds bounds of this TableComponent.
   */
  TableComponent(const ci::Rectf& bounds);

 protected:
  ci::Rectf bounds_;
};

/** Maintains functionality of a straight edge of the snooker table. */
class StraightEdge : public TableComponent {
 public:
  /**
   * Creates a new StraightEdge with the specified bounds.
   *
   * @param bounds bounds of this StraightEdge.
   */
  StraightEdge(const ci::Rectf& bounds);

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