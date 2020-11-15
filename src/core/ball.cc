/**
 * Created by Rishi Patel on 11/14/2020.
 */

#include "core/ball.h"
#include "cinder/gl/gl.h"

namespace snooker {

Ball::Ball(const glm::vec2& initial_position, const glm::vec2& initial_velocity,
           const ci::Color& color, float mass, float radius)
    : position_(initial_position),
      velocity_(initial_velocity),
      color_(color),
      mass_(mass),
      radius_(radius) {}

void Ball::UpdatePosition() {
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

}  // namespace snooker