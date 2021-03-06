/**
 * Created by Rishi Patel on 11/15/2020.
 */

#include "core/table.h"
#include "core/ball.h"
#include "core/table_cushion.h"
#include "core/pocket.h"
#include "cinder/gl/gl.h"

#include <algorithm>
#include <memory>
#include <vector>

namespace snooker {

Table::Table() : red_ball_count_(0) {
  walls_ = ci::Rectf(kHorizontalMargin, kVerticalMargin,
                     kHorizontalMargin + kTableWidth,
                     kVerticalMargin + kTableHeight);
  CreateCushions();
  CreateBalls();
  CreatePockets();
}

Table::Table(const ci::Rectf& walls, std::vector<TableCushionPtr> cushions)
    : walls_(walls),
      cushions_(std::move(cushions)),
      red_ball_count_(0) {}

void Table::AddBall(const Ball& ball) {
  if (walls_.contains(ball.GetPosition())) {
    balls_.push_back(ball);
    if (ball.GetColor() == Ball::kRed) {
      ++red_ball_count_;
    }
  }
  std::sort(balls_.begin(), balls_.end());
}

void Table::SimulateTimeStep() {
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

bool Table::IsSteady() const {
  for (const Ball& ball : balls_) {
    if (glm::length(ball.GetVelocity()) != 0) {
      return false;
    }
  }
  return true;
}

void Table::ResetFirstContacted() {
  for (Ball& ball : balls_) {
    ball.SetFirstContacted(Ball::kNoContactColor);
  }
}

void Table::RemoveBallFromTable(const Ball& ball) {
  for (size_t index_to_remove = 0; index_to_remove < balls_.size();
       ++index_to_remove) {
    if (ball == balls_[index_to_remove]) {
      if (ball.GetColor() == Ball::kRed) {
        --red_ball_count_;
      }
      balls_.erase(balls_.begin() + index_to_remove);
      return;
    }
  }
}

ci::Color Table::GetLeastPointValueColor() const {
  return balls_.front().GetColor();
}

void Table::SetCueBallVelocity(const glm::vec2& velocity) {
  balls_.back().SetVelocity(velocity);
}

void Table::SetCueBallFirstContacted(const ci::Color& color) {
  balls_.back().SetFirstContacted(color);
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

size_t Table::GetRedBallCount() const {
  return red_ball_count_;
}

const std::vector<Pocket>& Table::GetPockets() const {
  return pockets_;
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

void Table::CreateBalls() {
  float height = walls_.y2 - walls_.y1;
  float width = walls_.x2 - walls_.x1;
  glm::vec2 zero(0, 0);

  for (size_t row = 1; row <= 5; ++row) {
    glm::vec2 ball_position =
        glm::vec2(walls_.x1 + 0.75 * width + 2 * row * kBallRadius,
                  walls_.y1 + height / 2 - (row - 1) * kBallRadius);
    for (size_t ball_count = 1; ball_count <= row; ++ball_count) {
      AddBall(Ball(ball_position, zero, Ball::kRed, kBallRadius, kBallMass,
                   Ball::kRedBallValue));
      ball_position.y += 2 * kBallRadius;
    }
  }

  AddBall(Ball(glm::vec2(walls_.x1 + kBaulkLinePosition,
                         walls_.y1 + height / 2 + kSemicircleRadius),
               zero, Ball::kYellow, kBallRadius, kBallMass,
               Ball::kYellowBallValue));
  AddBall(Ball(glm::vec2(walls_.x1 + kBaulkLinePosition,
                         walls_.y1 + height / 2 - kSemicircleRadius),
               zero, Ball::kGreen, kBallRadius, kBallMass,
               Ball::kGreenBallValue));
  AddBall(
      Ball(glm::vec2(walls_.x1 + kBaulkLinePosition, walls_.y1 + height / 2),
           zero, Ball::kBrown, kBallRadius, kBallMass, Ball::kBrownBallValue));
  AddBall(Ball(glm::vec2(walls_.x1 + width / 2, walls_.y1 + height / 2), zero,
               Ball::kBlue, kBallRadius, kBallMass, Ball::kBlueBallValue));
  AddBall(Ball(glm::vec2(walls_.x1 + 0.75 * width, walls_.y1 + height / 2),
               zero, Ball::kPink, kBallRadius, kBallMass,
               Ball::kPinkBallValue));
  AddBall(Ball(glm::vec2(walls_.x1 + kTableWidth - kBlackBallGap,
                         walls_.y1 + height / 2),
               zero, Ball::kBlack, kBallRadius, kBallMass,
               Ball::kBlackBallValue));

  AddBall(Ball(glm::vec2(walls_.x1 + kBaulkLinePosition - kSemicircleRadius / 2,
                         walls_.y1 + height / 2 + kSemicircleRadius / 2),
               glm::vec2(0, 0), Ball::kWhite, kBallRadius, kBallMass,
               Ball::kWhiteBallValue));
}

void Table::CreatePockets() {
  pockets_.push_back(Pocket(glm::vec2(kHorizontalMargin + kCornerPocketRadius,
                                      kVerticalMargin + kCornerPocketRadius),
                            kCornerPocketRadius, Ball::kBlack));
  pockets_.push_back(
      Pocket(glm::vec2(kHorizontalMargin + kCornerPocketRadius,
                       kVerticalMargin + kTableHeight - kCornerPocketRadius),
             kCornerPocketRadius, Ball::kBlack));
  pockets_.push_back(
      Pocket(glm::vec2(kHorizontalMargin + kTableWidth - kCornerPocketRadius,
                       kVerticalMargin + kCornerPocketRadius),
             kCornerPocketRadius, Ball::kBlack));
  pockets_.push_back(
      Pocket(glm::vec2(kHorizontalMargin + kTableWidth - kCornerPocketRadius,
                       kVerticalMargin + kTableHeight - kCornerPocketRadius),
             kCornerPocketRadius, Ball::kBlack));
  pockets_.push_back(Pocket(glm::vec2(kHorizontalMargin + kTableWidth / 2,
                                      kVerticalMargin),
                            kSidePocketRadius, Ball::kBlack));
  pockets_.push_back(
      Pocket(glm::vec2(kHorizontalMargin + kTableWidth / 2,
                       kVerticalMargin + kTableHeight),
             kSidePocketRadius, Ball::kBlack));
}

}  // namespace snooker