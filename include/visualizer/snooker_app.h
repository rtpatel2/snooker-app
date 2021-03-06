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

  /** Dimensions of the end screen. */
  const float kEndScreenWidth = 300.0f;
  const float kEndScreenHeight = 200.0f;

 private:
  /** Draws the felt of the Table. */
  void DrawTableFelt() const;

  /** Draws the cushion of the Table. */
  void DrawCushions() const;

  /** Draws the rails of the Table. */
  void DrawRails() const;

  /** Draws the pockets of the Table. */
  void DrawPockets() const;

  /** Draws the snooker cue, when appropriate. */
  void DrawCue() const;

  /** Draws the Balls currently on the Table. */
  void DrawBalls() const;

  /** Draws which player who is currently at the Table. */
  void DrawCurrentPlayer() const;

  /** Draws each Player's score. */
  void DrawPlayerScores() const;

  /** Draws the screen to be displayed once the game is over. */
  void DrawEndGameScreen() const;

  const ci::Color kWhite = ci::Color("white");
  const ci::Color kBlack = ci::Color("black");
  const ci::Color kGray = ci::Color(77 / 255.0f, 100 / 255.0f, 108 / 255.0f);
  const ci::Color kFeltColor = ci::Color(0.227f, 0.71f, 0.0118f);
  const ci::Color kCushionColor = ci::Color(0.0392f, 0.424f, 0.0118f);
  const ci::Color kRailColor = ci::Color(0.502f, 0.251f, 0);
  const ci::Color kCueColor = ci::Color("brown");

  /** Fonts used for the text displayed on this GUI. */
  const ci::Font kDefaultFont = ci::Font("Century Gothic", 18);
  const ci::Font kLargeFont = ci::Font("Century Gothic", 36);

  Table table_;
  GameEngine engine_;
};

}  // namespace visualizer

}  // namespace snooker