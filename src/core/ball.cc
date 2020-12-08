/**
 * Created by Rishi Patel on 11/14/2020.
 */

#include "core/ball.h"
#include "cinder/gl/gl.h"

namespace snooker {

Ball::Ball(const glm::vec2& initial_position, const glm::vec2& initial_velocity,
           const ci::Color& color, float radius, float mass)
    : position_(initial_position),
      velocity_(initial_velocity * kTimeScaleFactor),
      color_(color),
      radius_(radius),
      mass_(mass) {
}

void Ball::UpdatePosition() {
  if (velocity_.y != 0 || velocity_.x != 0) {
    float angle = glm::atan(abs(velocity_.y) / abs(velocity_.x));
    float x_velocity_change = kFrictionWithTable * kGravityAcceleration *
                              kTimeScaleFactor * glm::cos(angle);
    float y_velocity_change = kFrictionWithTable * kGravityAcceleration *
                              kTimeScaleFactor * glm::sin(angle);
    velocity_.x = (abs(velocity_.x) - x_velocity_change <= 0) ? 0
                  : (velocity_.x > 0) ? velocity_.x - x_velocity_change
                                      : velocity_.x + x_velocity_change;
    velocity_.y = (abs(velocity_.y) - y_velocity_change <= 0) ? 0
                  : (velocity_.y > 0) ? velocity_.y - y_velocity_change
                                      : velocity_.y + y_velocity_change;
    position_ += velocity_;
  }
}

glm::vec2 Ball::ComputeVelocityAfterCollision(const Ball& other) const {
  // Formula sourced from:
  // https://wikimedia.org/api/rest_v1/media/math/render/svg
  // /14d5feb68844edae9e31c9cb4a2197ee922e409c.
  if (glm::distance(position_, other.position_) <= (radius_ + other.radius_) &&
      glm::dot(velocity_ - other.velocity_, position_ - other.position_) < 0) {
    glm::vec2 velocity_change = velocity_ - other.velocity_;
    glm::vec2 position_change = position_ - other.position_;
    return (velocity_ - ((2 * other.mass_) / (mass_ + other.mass_)) *
                            (glm::dot(velocity_change, position_change) /
                             pow(glm::length(position_change), 2)) *
                            (position_change));
  } else {
    return velocity_;
  }
}

const glm::vec2& Ball::GetPosition() const {
  return position_;
}

const glm::vec2& Ball::GetVelocity() const {
  return velocity_;
}

void Ball::SetVelocity(const glm::vec2& velocity) {
  velocity_ = velocity;
}

const ci::Color& Ball::GetColor() const {
  return color_;
}

float Ball::GetRadius() const {
  return radius_;
}

float Ball::GetMass() const {
  return mass_;
}

}  // namespace snooker