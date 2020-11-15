/**
 * Created by Rishi Patel on 11/14/2020.
 */

#pragma once

#include "core/table.h"
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

  /** Dimensions of the window -- margins on each side, plus central area. */
  const float kWindowWidth = 2 * kHorizontalMargin + kTableWidth;
  const float kWindowHeight = 2 * kVerticalMargin + kTableHeight;

 private:
  const ci::Color kWhite = ci::Color("white");
  const ci::Color kBlack = ci::Color("black");
  const ci::Color kRed = ci::Color("red");

  Table table_;
};

}  // namespace visualizer

}  // namespace snooker