/**
 * Created by Rishi Patel on 11/15/2020.
 */

#include "core/table.h"
#include "cinder/gl/gl.h"

namespace snooker {

Table::Table() {
  walls_ = ci::Rectf(kHorizontalMargin, kVerticalMargin,
                     kHorizontalMargin + kTableWidth,
                     kVerticalMargin + kTableHeight);
  CreateCushions();
}

Table::Table(const ci::Rectf& walls, std::vector<TableCushionPtr> cushions)
    : walls_(walls), cushions_(std::move(cushions)) {}

void Table::AddBall(const Ball& ball) {
  if (walls_.contains(ball.GetPosition())) {
    balls_.push_back(ball);
  }
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

    for (const TableCushionPtr& cushion : cushions_) {
      balls_[i].SetVelocity(cushion->ComputeVelocityAfterCollision(balls_[i]));
    }
    balls_[i].UpdatePosition();
  }
}

const std::vector<TableCushionPtr>& Table::GetCushions() const {
  return cushions_;
}

const ci::Rectf& Table::GetWalls() const {
  return walls_;
}

const std::vector<Ball>& Table::GetBalls() const {
  return balls_;
}

void Table::CreateCushions() {
  CreateLeftRightCushions();
  CreateSideCushions();
  CreateLeftPocketCushions();
  CreateSidePocketCushions();
  CreateRightPocketCushions();
}

void Table::CreateLeftRightCushions() {
  StraightCushionPtr left_cushion = std::make_unique<StraightCushion>(ci::Rectf(
      kHorizontalMargin, kVerticalMargin + kCushionWidth + kCornerPocketWidth,
      kHorizontalMargin + kCushionWidth,
      kVerticalMargin + kTableHeight - kCushionWidth - kCornerPocketWidth));

  StraightCushionPtr right_cushion =
      std::make_unique<StraightCushion>(ci::Rectf(
          kHorizontalMargin + kTableWidth - kCushionWidth,
          kVerticalMargin + kCushionWidth + kCornerPocketWidth,
          kHorizontalMargin + kTableWidth,
          kVerticalMargin + kTableHeight - kCushionWidth - kCornerPocketWidth));

  cushions_.push_back(std::move(left_cushion));
  cushions_.push_back(std::move(right_cushion));
}

void Table::CreateSideCushions() {
  StraightCushionPtr top_left_cushion = std::make_unique<StraightCushion>(
      ci::Rectf(kHorizontalMargin + kCushionWidth + kCornerPocketWidth,
                kVerticalMargin,
                kHorizontalMargin + kTableWidth / 2 - kSidePocketWidth,
                kVerticalMargin + kCushionWidth));

  StraightCushionPtr top_right_cushion =
      std::make_unique<StraightCushion>(ci::Rectf(
          kHorizontalMargin + kTableWidth / 2 + kSidePocketWidth,
          kVerticalMargin,
          kHorizontalMargin + kTableWidth - kCushionWidth - kCornerPocketWidth,
          kVerticalMargin + kCushionWidth));

  StraightCushionPtr bottom_left_cushion = std::make_unique<StraightCushion>(
      ci::Rectf(kHorizontalMargin + kCushionWidth + kCornerPocketWidth,
                kVerticalMargin + kTableHeight - kCushionWidth,
                kHorizontalMargin + kTableWidth / 2 - kSidePocketWidth,
                kVerticalMargin + kTableHeight));

  StraightCushionPtr bottom_right_cushion =
      std::make_unique<StraightCushion>(ci::Rectf(
          kHorizontalMargin + kTableWidth / 2 + kSidePocketWidth,
          kVerticalMargin + kTableHeight - kCushionWidth,
          kHorizontalMargin + kTableWidth - kCushionWidth - kCornerPocketWidth,
          kVerticalMargin + kTableHeight));

  cushions_.push_back(std::move(top_left_cushion));
  cushions_.push_back(std::move(top_right_cushion));
  cushions_.push_back(std::move(bottom_left_cushion));
  cushions_.push_back(std::move(bottom_right_cushion));
}

void Table::CreateLeftPocketCushions() {
  CurvedCushionPtr top_pocket_upper_cushion = std::make_unique<CurvedCushion>(
      glm::vec2(kHorizontalMargin + kCushionWidth + kCornerPocketWidth,
                kVerticalMargin),
      kCushionWidth);

  CurvedCushionPtr top_pocket_lower_cushion = std::make_unique<CurvedCushion>(
      glm::vec2(kHorizontalMargin,
                kVerticalMargin + kCushionWidth + kCornerPocketWidth),
      kCushionWidth);

  CurvedCushionPtr bottom_pocket_upper_cushion =
      std::make_unique<CurvedCushion>(
          glm::vec2(kHorizontalMargin, kVerticalMargin + kTableHeight -
                                           kCushionWidth - kCornerPocketWidth),
          kCushionWidth);

  CurvedCushionPtr bottom_pocket_lower_cushion =
      std::make_unique<CurvedCushion>(
          glm::vec2(kHorizontalMargin + kCushionWidth + kCornerPocketWidth,
                    kVerticalMargin + kTableHeight),
          kCushionWidth);

  cushions_.push_back(std::move(top_pocket_upper_cushion));
  cushions_.push_back(std::move(top_pocket_lower_cushion));
  cushions_.push_back(std::move(bottom_pocket_upper_cushion));
  cushions_.push_back(std::move(bottom_pocket_lower_cushion));
}

void Table::CreateSidePocketCushions() {
  CurvedCushionPtr top_pocket_left_cushion = std::make_unique<CurvedCushion>(
      glm::vec2(kHorizontalMargin + kTableWidth / 2 - kSidePocketWidth,
                kVerticalMargin),
      kCushionWidth);

  CurvedCushionPtr top_pocket_right_cushion = std::make_unique<CurvedCushion>(
      glm::vec2(kHorizontalMargin + kTableWidth / 2 + kSidePocketWidth,
                kVerticalMargin),
      kCushionWidth);

  CurvedCushionPtr bottom_pocket_left_cushion = std::make_unique<CurvedCushion>(
      glm::vec2(kHorizontalMargin + kTableWidth / 2 - kSidePocketWidth,
                kVerticalMargin + kTableHeight),
      kCushionWidth);

  CurvedCushionPtr bottom_pocket_right_cushion =
      std::make_unique<CurvedCushion>(
          glm::vec2(kHorizontalMargin + kTableWidth / 2 + kSidePocketWidth,
                    kVerticalMargin + kTableHeight),
          kCushionWidth);

  cushions_.push_back(std::move(top_pocket_left_cushion));
  cushions_.push_back(std::move(top_pocket_right_cushion));
  cushions_.push_back(std::move(bottom_pocket_left_cushion));
  cushions_.push_back(std::move(bottom_pocket_right_cushion));
}

void Table::CreateRightPocketCushions() {
  CurvedCushionPtr top_pocket_upper_cushion = std::make_unique<CurvedCushion>(
      glm::vec2(
          kHorizontalMargin + kTableWidth - kCushionWidth - kCornerPocketWidth,
          kVerticalMargin),
      kCushionWidth);

  CurvedCushionPtr top_pocket_lower_cushion = std::make_unique<CurvedCushion>(
      glm::vec2(kHorizontalMargin + kTableWidth,
                kVerticalMargin + kCushionWidth + kCornerPocketWidth),
      kCushionWidth);

  CurvedCushionPtr bottom_pocket_upper_cushion =
      std::make_unique<CurvedCushion>(
          glm::vec2(kHorizontalMargin + kTableWidth,
                    kVerticalMargin + kTableHeight - kCushionWidth -
                        kCornerPocketWidth),
          kCushionWidth);

  CurvedCushionPtr bottom_pocket_lower_cushion =
      std::make_unique<CurvedCushion>(
          glm::vec2(kHorizontalMargin + kTableWidth - kCushionWidth -
                        kCornerPocketWidth,
                    kVerticalMargin + kTableHeight),
          kCushionWidth);

  cushions_.push_back(std::move(top_pocket_upper_cushion));
  cushions_.push_back(std::move(top_pocket_lower_cushion));
  cushions_.push_back(std::move(bottom_pocket_upper_cushion));
  cushions_.push_back(std::move(bottom_pocket_lower_cushion));
}

}  // namespace snooker