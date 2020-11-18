/**
 * Created by Rishi Patel on 11/14/2020.
 */

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/table.h"
#include "core/table_cushion.h"

namespace snooker {

namespace visualizer {

/** Allows a user to visualize a game of snooker. */
class SnookerApp : public ci::app::App {
 public:
  /** Initializes a new SnookerApp. */
  SnookerApp();

  /** Performs once per loop computations to be used in draw(). */
  void update() override;

  /** Renders the current state of the snooker visualization. */
  void draw() override;

  /** Scaling factor for this visualization. */
  const float kScalingFactor = 2.5f;

  /** Size of the margins along the edges of the window. */
  const float kHorizontalMargin = 100.0f;
  const float kVerticalMargin = 100.0f;

  /** Dimensions of the table. */
  const float kTableWidth = 356.9f * kScalingFactor;
  const float kTableHeight = 177.8f * kScalingFactor;
  const float kBaulkLinePosition = 74 * kScalingFactor;
  const float kSemicircleRadius = 29 * kScalingFactor;
  const float kCushionWidth = 5 * kScalingFactor;
  const float kCornerPocketWidth = 11 * kScalingFactor;
  const float kSidePocketWidth = 10.5f * kScalingFactor;

  /** Dimensions of the window -- margins on each side, plus central area. */
  const float kWindowWidth = 2 * kHorizontalMargin + kTableWidth;
  const float kWindowHeight = 2 * kVerticalMargin + kTableHeight;

  /** Ball specifications. */
  const float kBallRadius = 2.625f * kScalingFactor;
  const float kBallMass = 3.0f;

  StraightCushion kLeftCushion = StraightCushion(ci::Rectf(
      kHorizontalMargin, kVerticalMargin + kCushionWidth + kCornerPocketWidth,
      kHorizontalMargin + kCushionWidth,
      kVerticalMargin + kTableHeight - kCushionWidth - kCornerPocketWidth));

  StraightCushion kRightCushion = StraightCushion(ci::Rectf(
      kHorizontalMargin + kTableWidth - kCushionWidth,
      kVerticalMargin + kCushionWidth + kCornerPocketWidth,
      kHorizontalMargin + kTableWidth,
      kVerticalMargin + kTableHeight - kCushionWidth - kCornerPocketWidth));

  StraightCushion kTopLeftCushion = StraightCushion(ci::Rectf(
      kHorizontalMargin + kCushionWidth + kCornerPocketWidth, kVerticalMargin,
      kHorizontalMargin + kTableWidth / 2 - kSidePocketWidth,
      kVerticalMargin + kCushionWidth));

  StraightCushion kTopRightCushion = StraightCushion(ci::Rectf(
      kHorizontalMargin + kTableWidth / 2 + kSidePocketWidth,
      kVerticalMargin,
      kHorizontalMargin + kTableWidth - kCushionWidth - kCornerPocketWidth,
      kVerticalMargin + kCushionWidth));

  StraightCushion kBottomLeftCushion = StraightCushion(
      ci::Rectf(kHorizontalMargin + kCushionWidth + kCornerPocketWidth,
                kVerticalMargin + kTableHeight - kCushionWidth,
                kHorizontalMargin + kTableWidth / 2 - kSidePocketWidth,
                kVerticalMargin + kTableHeight));

  StraightCushion kBottomRightCushion = StraightCushion(ci::Rectf(
      kHorizontalMargin + kTableWidth / 2 + kSidePocketWidth,
      kVerticalMargin + kTableHeight - kCushionWidth,
      kHorizontalMargin + kTableWidth - kCushionWidth - kCornerPocketWidth,
      kVerticalMargin + kTableHeight));

  CurvedCushion kTopLeftPocketTopCushion = CurvedCushion(
      glm::vec2(kHorizontalMargin + kCushionWidth + kCornerPocketWidth,
                kVerticalMargin),
      kCushionWidth);

  CurvedCushion kTopLeftPocketBottomCushion = CurvedCushion(
      glm::vec2(kHorizontalMargin,
                kVerticalMargin + kCushionWidth + kCornerPocketWidth),
      kCushionWidth);

  CurvedCushion kBottomLeftPocketTopCushion = CurvedCushion(
      glm::vec2(kHorizontalMargin, kVerticalMargin + kTableHeight -
                                       kCushionWidth - kCornerPocketWidth),
      kCushionWidth);

  CurvedCushion kBottomLeftPocketBottomCushion = CurvedCushion(
      glm::vec2(kHorizontalMargin + kCushionWidth + kCornerPocketWidth,
                kVerticalMargin + kTableHeight),
      kCushionWidth);

  CurvedCushion kTopPocketLeftCushion = CurvedCushion(
      glm::vec2(kHorizontalMargin + kTableWidth / 2 - kSidePocketWidth,
                kVerticalMargin),
      kCushionWidth);

  CurvedCushion kTopPocketRightCushion = CurvedCushion(
      glm::vec2(kHorizontalMargin + kTableWidth / 2 + kSidePocketWidth,
                kVerticalMargin),
      kCushionWidth);

  CurvedCushion kBottomPocketLeftCushion = CurvedCushion(
      glm::vec2(kHorizontalMargin + kTableWidth / 2 - kSidePocketWidth,
                kVerticalMargin + kTableHeight),
      kCushionWidth);

  CurvedCushion kBottomPocketRightCushion = CurvedCushion(
      glm::vec2(kHorizontalMargin + kTableWidth / 2 + kSidePocketWidth,
                kVerticalMargin + kTableHeight),
      kCushionWidth);

  CurvedCushion kTopRightPocketTopCushion =
      CurvedCushion(glm::vec2(kHorizontalMargin + kTableWidth - kCushionWidth -
                                  kCornerPocketWidth,
                              kVerticalMargin),
                    kCushionWidth);

  CurvedCushion kTopRightPocketBottomCushion = CurvedCushion(
      glm::vec2(kHorizontalMargin + kTableWidth,
                kVerticalMargin + kCushionWidth + kCornerPocketWidth),
      kCushionWidth);

  CurvedCushion kBottomRightPocketTopCushion =
      CurvedCushion(glm::vec2(kHorizontalMargin + kTableWidth,
                              kVerticalMargin + kTableHeight - kCushionWidth -
                                  kCornerPocketWidth),
                    kCushionWidth);

  CurvedCushion kBottomRightPocketBottomCushion = CurvedCushion(
      glm::vec2(kHorizontalMargin + kTableWidth - kCushionWidth -
                kCornerPocketWidth,
                kVerticalMargin + kTableHeight),
      kCushionWidth);

 private:
  const ci::Color kWhite = ci::Color("white");
  const ci::Color kBlack = ci::Color("black");
  const ci::Color kTableColor = ci::Color(0.227f, 0.71f, 0.0118f);
  const ci::Color kCushionColor = ci::Color(0.0392f, 0.424f, 0.0118f);
  const ci::Color kRailColor = ci::Color(0.502f, 0.251f, 0);
  const ci::Color kRed = ci::Color("red");
  const ci::Color kBrown = ci::Color("brown");

  Table table_;
};

}  // namespace visualizer

}  // namespace snooker