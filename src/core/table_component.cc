/**
 * Created by Rishi Patel on 11/15/2020.
 */

#include "core/table_component.h"
#include "cinder/gl/gl.h"

namespace snooker {

TableComponent::TableComponent() = default;

StraightEdge::StraightEdge(const ci::Rectf& bounds)
    : bounds_(bounds) {}

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

const ci::Rectf& StraightEdge::GetBounds() const {
  return bounds_;
}

CurvedEdge::CurvedEdge(const glm::vec2& position, float radius)
    : position_(position), radius_(radius) {}

glm::vec2 CurvedEdge::ComputeVelocityAfterCollision(const Ball& ball) const {
  // Mathematically, this is identical to a collision between two Balls, but
  // the CurvedEdge has infinite mass (i.e., cannot be moved).
  glm::vec2 ball_position = ball.GetPosition();
  glm::vec2 velocity = ball.GetVelocity();
  if (glm::distance(ball_position, position_) <= (ball.GetRadius() + radius_) &&
      glm::dot(velocity, ball_position - position_) < 0) {
    glm::vec2 position_change = ball_position - position_;
    return (velocity - 2 * (glm::dot(velocity, position_change) /
                            pow(glm::length(position_change), 2)) *
                           (position_change));
  } else {
    return velocity;
  }
}

const glm::vec2& CurvedEdge::GetPosition() const {
  return position_;
}

float CurvedEdge::GetRadius() const {
  return radius_;
}

}  // namespace snooker