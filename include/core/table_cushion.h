/**
 * Created by Rishi Patel on 11/15/2020.
 */

#pragma once

#include "core/ball.h"
#include "cinder/gl/gl.h"

namespace snooker {

/** Maintains functionality of a single cushion of a snooker table. */
class TableCushion {
 public:
  TableCushion();

  /**
   * Computes the velocity of a Ball after collision with this TableCushion.
   *
   * @param ball snooker Ball colliding with table.
   * @return velocity of the Ball after collision.
   */
  virtual glm::vec2 ComputeVelocityAfterCollision(const Ball& ball) const = 0;
};

/** Maintains functionality of a straight cushion of the snooker table. */
class StraightCushion : public TableCushion {
 public:
  /**
   * Creates a new StraightCushion with the specified bounds.
   *
   * @param bounds bounds of this StraightCushion.
   */
  explicit StraightCushion(const ci::Rectf& bounds);

  /**
   * Computes the velocity of a Ball after collision with this StraightCushion.
   *
   * @param ball snooker Ball colliding with cushion.
   * @return velocity of the Ball after collision.
   */
  glm::vec2 ComputeVelocityAfterCollision(const Ball& ball) const override;

  const ci::Rectf& GetBounds() const;

 private:
  ci::Rectf bounds_;
};

/** Maintains functionality of a curved cushion of the snooker table. */
class CurvedCushion : public TableCushion {
 public:
  /**
   * Creates a new CurvedCushion with the specified bounds.
   *
   * @param position position of this CurvedCushion.
   * @param radius radius of this CurvedCushion.
   */
  CurvedCushion(const glm::vec2& position, float radius);

  /**
   * Computes the velocity of a Ball after collision with this CurvedCushion.
   *
   * @param ball snooker Ball colliding with cushion.
   * @return velocity of the Ball after collision.
   */
  glm::vec2 ComputeVelocityAfterCollision(const Ball& ball) const override;

  const glm::vec2& GetPosition() const;
  float GetRadius() const;

 private:
  glm::vec2 position_;
  float radius_;
};

}  // namespace snooker