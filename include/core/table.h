/**
 * Created by Rishi Patel on 11/15/2020.
 */

#pragma once

#include "ball.h"
#include "table_cushion.h"
#include "pocket.h"
#include "cinder/gl/gl.h"

#include <memory>
#include <vector>

typedef std::unique_ptr<snooker::TableCushion> TableCushionPtr;
typedef std::unique_ptr<snooker::StraightCushion> StraightCushionPtr;
typedef std::unique_ptr<snooker::CurvedCushion> CurvedCushionPtr;

namespace snooker {

/** Maintains functionality of a snooker table. */
class Table {
 public:
  /**
   * Creates a new Table with standard snooker configuration.
   */
  Table();

  /**
   * Creates a new Table with the specified walls and TableCushions.
   *
   * @param walls walls for this Table.
   * @param cushions TableCushions for this Table.
   */
  Table(const ci::Rectf& walls, std::vector<TableCushionPtr> cushions);

  /**
   * Adds the specified Ball to this Table if the Ball is within the Table's
   * bounds.
   *
   * @param ball Ball to add.
   */
  void AddBall(const Ball& ball);

  /**
   * Updates the velocities and positions of all Balls, simulating the
   * passage of one unit of time.
   */
  void IncrementTime();

  /**
   * Determines whether or not all Balls on this Table have stopped moving.
   *
   * @return true if no Balls are still moving, and false otherwise.
   */
  bool IsSteady() const;

  /**
   * Sets the velocity of the cue ball to the specified velocity.
   *
   * @param velocity velocity to which to set cue ball velocity.
   */
  void SetCueBallVelocity(const glm::vec2& velocity);

  /** Resets the first contacted Ball pointer from all Balls on the Table. */
  void ResetFirstContacted();

  /**
   * Removes the given Ball from this Table.
   *
   * @param ball pointer to the Ball to remove.
   */
  void RemoveBallFromTable(const Ball& ball);

  /**
   * Determines the color with lowest point value still on the Table.
   *
   * @return color of the lowest point value Ball.
   */
  ci::Color DetermineLeastPointsColor() const;

  const std::vector<TableCushionPtr>& GetCushions() const;
  const ci::Rectf& GetWalls() const;
  const std::vector<Ball>& GetBalls() const;
  size_t GetRedBallCount() const;
  const std::vector<Pocket>& GetPockets() const;

  /** Constants relevant to creation of a default Table. */
  static constexpr float kHorizontalMargin = 100.0f;
  static constexpr float kVerticalMargin = 100.0f;
  static constexpr float kScalingFactor = 2.5f;
  static constexpr float kCueStrokeFactor = 6.0f;

  static constexpr float kTableWidth = 356.9f * kScalingFactor;
  static constexpr float kTableHeight = 177.8f * kScalingFactor;
  static constexpr float kBaulkLinePosition = 74 * kScalingFactor;
  static constexpr float kBlackBallGap = 32.385f * kScalingFactor;
  static constexpr float kSemicircleRadius = 29 * kScalingFactor;
  static constexpr float kCushionWidth = 5 * kScalingFactor;
  static constexpr float kCornerPocketWidth = 11 * kScalingFactor;
  static constexpr float kSidePocketWidth = 10.5f * kScalingFactor;
  static constexpr float kCornerPocketRadius = kCornerPocketWidth / 2;
  static constexpr float kSidePocketRadius = kSidePocketWidth / 2;

  /** Ball specifications. */
  static constexpr float kBallRadius = 2.625f * Table::kScalingFactor;
  static constexpr float kBallMass = 3.0f;

  /** Cue specifications. */
  static constexpr float kCueLength = 100 * Table::kScalingFactor;
  static constexpr float kCueWidth = 1 * Table::kScalingFactor;
  static constexpr float kMaxPullBack = 25 * Table::kScalingFactor;

 private:
  /** Creates standard cushions for this Table based on its dimensions. */
  void CreateCushions();

  /** Creates the left and right cushions for this Table. */
  void CreateLeftRightCushions();

  /** Creates side cushions for this Table. */
  void CreateSideCushions();

  /** Creates the cushions lining the inside of the left rail pockets. */
  void CreateLeftPocketCushions();

  /** Creates the cushions lining the inside of the side pockets. */
  void CreateSidePocketCushions();

  /** Creates the cushions lining the inside of the right rail pockets. */
  void CreateRightPocketCushions();

  /** Creates and places all balls for a standard game of snooker. */
  void CreateBalls();

  /** Creates and places all pockets for a standard game of snooker. */
  void CreatePockets();

  std::vector<TableCushionPtr> cushions_;
  ci::Rectf walls_;
  std::vector<Ball> balls_;
  size_t red_ball_count_;
  std::vector<Pocket> pockets_;
};

}  // namespace snooker