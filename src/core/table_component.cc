/**
 * Created by Rishi Patel on 11/15/2020.
 */

#include "core/table_component.h"
#include "cinder/gl/gl.h"

namespace snooker {

TableComponent::TableComponent(const ci::Rectf& bounds)
    : bounds_(bounds) {}

StraightEdge::StraightEdge(const ci::Rectf& bounds)
    : TableComponent(bounds) {}

glm::vec2 StraightEdge::ComputeVelocityAfterCollision(const Ball& ball) const {
  glm::vec2 velocity = ball.GetVelocity();
  glm::vec2 position = ball.GetPosition();
  if (bounds_.y1 <= position.y && position.y <= bounds_.y2) {
    if ((velocity.x < 0 && bounds_.x2 <= position.x &&
         abs(bounds_.x2 - position.x) <= ball.GetRadius()) ||
        (velocity.x > 0 && bounds_.x1 >= position.x &&
         abs(bounds_.x1 - position.x) <= ball.GetRadius())) {
      glm::vec2 final_velocity = velocity;
      final_velocity.x *= -Ball::kRestitutionCoefficient;
      return final_velocity;
    }
  }

  if (bounds_.x1 <= position.x && position.x <= bounds_.x2) {
    if ((velocity.y < 0 && bounds_.y2 <= position.y &&
         abs(bounds_.y2 - position.y) <= ball.GetRadius()) ||
        (velocity.y > 0 && bounds_.y1 >= position.y &&
         abs(bounds_.y1 - position.y) <= ball.GetRadius())) {
      glm::vec2 final_velocity = velocity;
      final_velocity.y *= -Ball::kRestitutionCoefficient;
      return final_velocity;
    }
  }
  return velocity;
}

const ci::Rectf& TableComponent::GetBounds() const {
  return bounds_;
}

}  // namespace snooker