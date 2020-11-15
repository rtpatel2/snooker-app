/**
 * Created by Rishi Patel on 11/14/2020.
 */

#include "core/ball.h"
#include "cinder/gl/gl.h"

namespace snooker {

Ball::Ball(const glm::vec2& initial_position, const glm::vec2& initial_velocity,
           const ci::Color& color, float radius, float mass)
    : position_(initial_position),
      velocity_(initial_velocity),
      color_(color),
      radius_(radius),
      mass_(mass) {
}

void Ball::UpdatePosition() {
  float velocity_change = kFrictionWithTable * kGravityAcceleration;
  velocity_.x = (abs(velocity_.x) - velocity_change <= 0) ? 0
                : (velocity_.x > 0) ? velocity_.x - velocity_change
                                    : velocity_.x + velocity_change;
  velocity_.y = (abs(velocity_.y) - velocity_change <= 0) ? 0
                : (velocity_.y > 0) ? velocity_.y - velocity_change
                                    : velocity_.y + velocity_change;
  position_ += velocity_;
}

void Ball::CollideWithTableWalls(const ci::Rectf& walls) {
  if ((abs(walls.x1 - position_.x) <= radius_ && velocity_.x < 0) ||
      (abs(walls.x2 - position_.x) <= radius_ && velocity_.x > 0)) {
    velocity_.x *= -1;
  }

  if ((abs(walls.y1 - position_.y) <= radius_ && velocity_.y < 0) ||
      (abs(walls.y2 - position_.y) <= radius_ && velocity_.y > 0)) {
    velocity_.y *= -1;
  }
}

glm::vec2 Ball::ComputeVelocityAfterCollision(const Ball& other) const {
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