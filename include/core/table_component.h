/**
 * Created by Rishi Patel on 11/15/2020.
 */

#pragma once

#include "core/ball.h"
#include "cinder/gl/gl.h"
#include "cinder/svg/Svg.h"

namespace snooker {

/** Maintains functionality of a single component of a snooker table. */
class TableComponent {
 public:
  TableComponent();

  /**
   * Computes the velocity of a Ball after collision with this TableComponent.
   *
   * @param ball snooker Ball colliding with table.
   * @return velocity of the Ball after collision.
   */
  virtual glm::vec2 ComputeVelocityAfterCollision(const Ball& ball) const = 0;

  virtual const ci::svg::Node& GetBounds() const = 0;
};

/** Maintains functionality of a straight edge of the snooker table. */
class StraightEdge : public TableComponent {
 public:
  /**
   * Creates a new StraightEdge with the specified bounds.
   *
   * @param bounds bounds of this StraightEdge.
   */
  explicit StraightEdge(const ci::svg::Rect& bounds);

  /**
   * Computes the velocity of a Ball after collision with this StraightEdge.
   *
   * @param ball snooker Ball colliding with edge.
   * @return velocity of the Ball after collision.
   */
  glm::vec2 ComputeVelocityAfterCollision(const Ball& ball) const override;

  const ci::svg::Rect& GetBounds() const;

 private:
  ci::svg::Rect bounds_;
};

/** Maintains functionality of a curved edge of the snooker table. */
class CurvedEdge : public TableComponent {
 public:
  /**
   * Creates a new CurvedEdge with the specified bounds.
   *
   * @param bounds bounds of this StraightEdge.
   */
  CurvedEdge(const ci::svg::Circle& bounds);

  /**
   * Computes the velocity of a Ball after collision with this CurvedEdge.
   *
   * @param ball snooker Ball colliding with edge.
   * @return velocity of the Ball after collision.
   */
  glm::vec2 ComputeVelocityAfterCollision(const Ball& ball) const override;

  const ci::svg::Circle& GetBounds() const;

 private:
  ci::svg::Circle bounds_;
};

}  // namespace snooker