/**
 * Created by Rishi Patel on 11/14/2020.
 */

#pragma once

#include "cinder/gl/gl.h"

namespace snooker {

/** Maintains functionality of a snooker ball. */
class Ball {
 public:
  /**
   * Creates a new snooker Ball with the specified initial position, initial
   * velocity, color, radius, and mass.
   *
   * @param initial_position initial position of the Ball.
   * @param initial_velocity initial velocity of the Ball.
   * @param color color of the Ball.
   * @param radius radius of the Ball.
   * @param mass mass of the Ball.
   */
  Ball(const glm::vec2& initial_position, const glm::vec2& initial_velocity,
       const ci::Color& color, float radius, float mass);

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

  /**
   * Computes the velocity of this Ball after colliding elastically with the
   * given Ball.
   *
   * @param other Ball with which this Ball is colliding.
   * @return velocity of this Ball after collision.
   */
  glm::vec2 ComputeVelocityAfterCollision(const Ball& other) const;

  const glm::vec2& GetPosition() const;
  const glm::vec2& GetVelocity() const;
  void SetVelocity(const glm::vec2& velocity);
  const ci::Color& GetColor() const;
  float GetRadius() const;
  float GetMass() const;

  const float kGravityAcceleration = 980.0f;
  const float kFrictionWithTable = 0.001f;

 public:
  glm::vec2 position_;
  glm::vec2 velocity_;
  ci::Color color_;
  float mass_;
  float radius_;
};

}  // namespace snooker