/**
 * Created by Rishi Patel on 11/15/2020.
 */

#pragma once

#include "ball.h"
#include "cinder/gl/gl.h"
#include "table_cushion.h"

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

  const std::vector<TableCushionPtr>& GetCushions() const;
  const ci::Rectf& GetWalls() const;
  const std::vector<Ball>& GetBalls() const;

  /** Constants relevant to creation of a default Table. */
  static constexpr float kHorizontalMargin = 100.0f;
  static constexpr float kVerticalMargin = 100.0f;
  static constexpr float kScalingFactor = 2.5f;

  static constexpr float kTableWidth = 356.9f * kScalingFactor;
  static constexpr float kTableHeight = 177.8f * kScalingFactor;
  static constexpr float kBaulkLinePosition = 74 * kScalingFactor;
  static constexpr float kSemicircleRadius = 29 * kScalingFactor;
  static constexpr float kCushionWidth = 5 * kScalingFactor;
  static constexpr float kCornerPocketWidth = 11 * kScalingFactor;
  static constexpr float kSidePocketWidth = 10.5f * kScalingFactor;

 private:
  /** Creates cushions for this Table based on its position and dimensions. */
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

  std::vector<TableCushionPtr> cushions_;
  ci::Rectf walls_;
  std::vector<Ball> balls_;
};

}  // namespace snooker