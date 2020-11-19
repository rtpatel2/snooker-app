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

  /** Dimensions of the window -- margins on each side, plus central area. */
  const float kWindowWidth = 2 * Table::kHorizontalMargin + Table::kTableWidth;
  const float kWindowHeight = 2 * Table::kVerticalMargin + Table::kTableHeight;

  /** Ball specifications. */
  const float kBallRadius = 2.625f * Table::kScalingFactor;
  const float kBallMass = 3.0f;

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