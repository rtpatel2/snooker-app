//
// Created by infernus on 11/29/2020.
//

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

}  // namespace snooker