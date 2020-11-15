/**
 * Created by Rishi Patel on 11/14/2020.
 */

#pragma once

#include "cinder/gl/gl.h"

namespace snooker {

/** Maintains functionality of a snooker Ball. */
class Ball {
 public:
  /**
   * Creates a new snooker Ball with the specified position, velocity, color,
   * mass, and radius.
   *
   * @param initial_position initial position of the Ball.
   * @param initial_velocity initial velocity of the Ball.
   * @param color color of the Ball.
   * @param mass mass of the Ball.
   * @param radius radius of the Ball.
   */
  Ball(const glm::vec2& initial_position, const glm::vec2& initial_velocity,
       const ci::Color& color, float mass, float radius);

  /**
   * Updates the position of this Ball, simulating the passage of one unit of
   * time.
   */
  void UpdatePosition();

  /**
   * Modifies the velocity of this Ball after collision with the provided
   * rectangular bounds.
   *
   * @param walls walls with which the Ball is colliding.
   */
  void CollideWithTableWalls(const ci::Rectf& walls);

 public:
  glm::vec2 position_;
  glm::vec2 velocity_;
  ci::Color color_;
  float mass_;
  float radius_;
};

}  // namespace snooker