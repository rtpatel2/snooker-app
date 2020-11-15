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

}  // namespace snooker