/**
 * Created by Rishi Patel on 11/15/2020.
 */

#include "core/table.h"
#include "cinder/gl/gl.h"

namespace snooker {

Table::Table() = default;

Table::Table(const ci::Rectf& walls,
             const std::vector<TableCushion*>& cushions)
    : walls_(walls), cushions_(cushions) {
}

void Table::AddBall(const Ball& ball) {
  if (walls_.contains(ball.GetPosition())) {
    balls_.push_back(ball);
  }
}

void Table::AddCushion(TableCushion* cushion) {
  cushions_.push_back(cushion);
}

void Table::IncrementTime() {
  for (size_t i = 0; i < balls_.size(); ++i) {
    for (size_t j = i + 1; j < balls_.size(); ++j) {
      glm::vec2 particle1_new_velocity =
          balls_[i].ComputeVelocityAfterCollision(balls_[j]);
      glm::vec2 particle2_new_velocity =
          balls_[j].ComputeVelocityAfterCollision(balls_[i]);
      balls_[i].SetVelocity(particle1_new_velocity);
      balls_[j].SetVelocity(particle2_new_velocity);
    }

    for (const TableCushion* cushion : cushions_) {
      balls_[i].SetVelocity(cushion->ComputeVelocityAfterCollision(balls_[i]));
    }
    balls_[i].UpdatePosition();
  }
}

void Table::ClearTable() {
  balls_.clear();
}

const std::vector<TableCushion*>& Table::GetCushions() const {
  return cushions_;
}

const ci::Rectf& Table::GetWalls() const {
  return walls_;
}

const std::vector<Ball>& Table::GetBalls() const {
  return balls_;
}

}  // namespace snooker