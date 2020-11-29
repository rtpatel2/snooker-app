/**
 * Created by Rishi Patel on 11/29/2020.
 */

#pragma once

#include "ball.h"
#include "cinder/gl/gl.h"

namespace snooker {

/** Maintains functionality of a pocket on a snooker Table. */
class Pocket {
 public:
  /**
   * Creates a new Pocket for a snooker Table.
   *
   * @param position position of this Pocket.
   * @param radius radius of this Pocket.
   * @param color color of this Pocket.
   */
  Pocket(const glm::vec2& position, float radius, const ci::Color& color);

  /**
   * Determines if the given Ball will be pocketed in this Pocket.
   *
   * @param ball Ball to determine whether or not will be pocketed.
   * @return true if the Ball will be pocketed, and false otherwise.
   */
  bool DetermineIfPocketed(const Ball& ball) const;

 private:
  glm::vec2 position_;
  float radius_;
  ci::Color color_;
};

}  // namespace snooker