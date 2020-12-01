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
   * @param point_value point value of the Ball.
   */
  Ball(const glm::vec2& initial_position, const glm::vec2& initial_velocity,
       const ci::Color& color, float radius, float mass, size_t point_value);

  /** Updates position of this Ball, simulating passage of one unit of time. */
  void UpdatePosition();

  /**
   * Computes the velocity of this Ball after colliding elastically with the
   * given Ball.
   *
   * @param other Ball with which this Ball is colliding.
   * @return velocity of this Ball after collision.
   */
  glm::vec2 ComputeVelocityAfterCollision(Ball& other);

  /**
   * Compares this Ball for equality with the given Ball, determined by
   * whether or not the two Balls have the same initial position.
   *
   * @param other Ball to compare to.
   * @return true if the Balls are equal, and false otherwise.
   */
  bool operator==(const Ball& other) const;

  /**
   * Compares Balls by point value, for sorting purposes.
   *
   * @param other Ball to which to compare this Ball.
   * @return true if this Ball has a lower point value than the other Ball,
   * and false otherwise.
   */
  bool operator<(const Ball& other) const;

  const glm::vec2& GetPosition() const;
  const glm::vec2& GetVelocity() const;
  const glm::vec2& GetInitialPosition() const;
  void SetVelocity(const glm::vec2& velocity);
  const ci::Color& GetColor() const;
  float GetRadius() const;
  float GetMass() const;
  const ci::Color& GetFirstContacted() const;
  void SetFirstContacted(const ci::Color& color);
  size_t GetPointValue() const;

  static constexpr float kGravityAcceleration = 980.0f;
  static constexpr float kFrictionWithTable = 0.004f;
  static constexpr float kRestitutionCoefficient = 0.95f;
  static constexpr float kTimeScaleFactor = 0.01f;
  static constexpr float kMarginOfError = 0.01f;

  /** Ball colors. */
  static const ci::Color kRed;
  static const ci::Color kBlack;
  static const ci::Color kWhite;
  static const ci::Color kGreen;
  static const ci::Color kYellow;
  static const ci::Color kPink;
  static const ci::Color kBrown;
  static const ci::Color kBlue;
  static const ci::Color kNoContactColor;

 private:
  glm::vec2 position_;
  glm::vec2 velocity_;
  glm::vec2 initial_position_;
  ci::Color color_;
  float mass_;
  float radius_;
  ci::Color first_contacted_;
  size_t point_value_;
};

}  // namespace snooker