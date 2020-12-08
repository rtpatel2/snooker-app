/**
 * Created by Rishi Patel on 11/29/2020.
 */

#include "core/pocket.h"
#include "core/ball.h"
#include "cinder/gl/gl.h"

namespace snooker {

Pocket::Pocket(const glm::vec2& position, float radius, const ci::Color& color)
    : position_(position), radius_(radius), color_(color) {}

bool Pocket::DetermineIfPocketed(const Ball& ball) const {
  if (glm::distance(position_, ball.GetPosition()) <= radius_) {
    return true;
  } else {
    return false;
  }
}

const glm::vec2& Pocket::GetPosition() const {
  return position_;
}

float Pocket::GetRadius() const {
  return radius_;
}

const ci::Color& Pocket::GetColor() const {
  return color_;
}

}  // namespace snooker