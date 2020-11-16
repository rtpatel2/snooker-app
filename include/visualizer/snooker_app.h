/**
 * Created by Rishi Patel on 11/14/2020.
 */

#pragma once

#include "core/table.h"
#include "core/table_component.h"
#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

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
  const float kCornerPocketWidth = 8.13f * kScalingFactor;
  const float kSidePocketWidth = 13 * kScalingFactor;

  /** Dimensions of the window -- margins on each side, plus central area. */
  const float kWindowWidth = 2 * kHorizontalMargin + kTableWidth;
  const float kWindowHeight = 2 * kVerticalMargin + kTableHeight;

  /** Ball specifications. */
  const float kBallRadius = 2.625f * kScalingFactor;
  const float kBallMass = 3.0f;

  StraightEdge kLeftCushion = StraightEdge(ci::Rectf(
      kHorizontalMargin, kVerticalMargin + kCushionWidth + kCornerPocketWidth,
      kHorizontalMargin + kCushionWidth,
      kVerticalMargin + kTableHeight - kCushionWidth - kCornerPocketWidth));

  StraightEdge kRightCushion = StraightEdge(ci::Rectf(
      kHorizontalMargin + kTableWidth - kCushionWidth,
      kVerticalMargin + kCushionWidth + kCornerPocketWidth,
      kHorizontalMargin + kTableWidth,
      kVerticalMargin + kTableHeight - kCushionWidth - kCornerPocketWidth));

  StraightEdge kTopLeftCushion = StraightEdge(ci::Rectf(
      kHorizontalMargin + kCushionWidth + kCornerPocketWidth, kVerticalMargin,
      kHorizontalMargin + kTableWidth / 2 - kSidePocketWidth / 2,
      kVerticalMargin + kCushionWidth));

  StraightEdge kTopRightCushion = StraightEdge(ci::Rectf(
      kHorizontalMargin + kTableWidth / 2 + kSidePocketWidth / 2,
      kVerticalMargin,
      kHorizontalMargin + kTableWidth - kCushionWidth - kCornerPocketWidth,
      kVerticalMargin + kCushionWidth));

  StraightEdge kBottomLeftCushion = StraightEdge(
      ci::Rectf(kHorizontalMargin + kCushionWidth + kCornerPocketWidth,
                kVerticalMargin + kTableHeight - kCushionWidth,
                kHorizontalMargin + kTableWidth / 2 - kSidePocketWidth / 2,
                kVerticalMargin + kTableHeight));

  StraightEdge kBottomRightCushion = StraightEdge(ci::Rectf(
      kHorizontalMargin + kTableWidth / 2 + kSidePocketWidth / 2,
      kVerticalMargin + kTableHeight - kCushionWidth,
      kHorizontalMargin + kTableWidth - kCushionWidth - kCornerPocketWidth,
      kVerticalMargin + kTableHeight));

  CurvedEdge kTopLeftPocketBottomCushion =
      CurvedEdge(glm::vec2(kHorizontalMargin, kVerticalMargin + kCushionWidth +
                                                  kCornerPocketWidth),
                 kCushionWidth);

  CurvedEdge kTopLeftPocketTopCushion = CurvedEdge(
      glm::vec2(kHorizontalMargin + kCushionWidth + kCornerPocketWidth,
                kVerticalMargin),
      kCushionWidth);

  CurvedEdge kBottomLeftPocketTopCushion = CurvedEdge(
      glm::vec2(kHorizontalMargin, kVerticalMargin + kTableHeight -
                                       kCushionWidth - kCornerPocketWidth),
      kCushionWidth);

  CurvedEdge kBottomLeftPocketBottomCushion = CurvedEdge(
      glm::vec2(kHorizontalMargin + kCushionWidth + kCornerPocketWidth,
                kVerticalMargin + kTableHeight),
      kCushionWidth);

 private:
  const ci::Color kWhite = ci::Color("white");
  const ci::Color kBlack = ci::Color("black");
  const ci::Color kTableColor = ci::Color(0.227f, 0.71f, 0.0118f); // green
  const ci::Color kCushionColor = ci::Color(0.0392f, 0.424f, 0.0118f);
  const ci::Color kRailColor = ci::Color(0.502f, 0.251f, 0); // dark brown
  const ci::Color kRed = ci::Color("red");
  const ci::Color kBrown = ci::Color("brown");

  Table table_;
};

}  // namespace visualizer

}  // namespace snooker