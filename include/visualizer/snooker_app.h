/**
 * Created by Rishi Patel on 11/14/2020.
 */

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/table.h"
#include "core/table_cushion.h"
#include "core/player.h"
#include "core/game_engine.h"

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

  /** Receives and handles mouse-up events. */
  void mouseUp(ci::app::MouseEvent event) override;

  /** Receives and handles mouse-down events. */
  void mouseDown(ci::app::MouseEvent event) override;

  /** Handles cue movement while dragging the mouse. */
  void mouseDrag(ci::app::MouseEvent event) override;

  /** Dimensions of the window -- margins on each side, plus central area. */
  const float kWindowWidth = 2 * Table::kHorizontalMargin + Table::kTableWidth;
  const float kWindowHeight = 2 * Table::kVerticalMargin + Table::kTableHeight;

 private:
  const ci::Color kWhite = ci::Color("white");
  const ci::Color kBlack = ci::Color("black");
  const ci::Color kTableColor = ci::Color(0.227f, 0.71f, 0.0118f);
  const ci::Color kCushionColor = ci::Color(0.0392f, 0.424f, 0.0118f);
  const ci::Color kRailColor = ci::Color(0.502f, 0.251f, 0);

  Table table_;
  GameEngine engine_;
};

}  // namespace visualizer

}  // namespace snooker