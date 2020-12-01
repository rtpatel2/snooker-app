/**
 * Created by Rishi Patel on 11/28/2020.
 */

#pragma once

#include "table.h"
#include "player.h"

namespace snooker {

/** Maintains game logic and control flow of a game of snooker. */
class GameEngine {
 public:
  GameEngine(Table* table);

  /** Handles the logic behind pocketing Balls. */
  void PocketBalls();

  /** Handles the logic behind spotting Balls, when appropriate. */
  void SpotBalls();

  /**
   * Determines whether or not Player 1 is currently at the Table.
   *
   * @return true if Player 1 is at the table, and false otherwise.
   */
  bool IsPlayer1Turn() const;

  /**
 * Handles logic pertaining to the start of a stroke.
 *
 * @param start_position the position of the stroke start.
 */
  void HandleStrokeStart(const glm::vec2& start_position);

  /**
   * Handles logic pertaining to the pulling back of the cue.
   *
   * @param mouse_position current position of the mouse.
   */
  void HandleCuePullBack(const glm::vec2& mouse_position);

  /**
   * Handles logic pertaining to the end of a stroke.
   *
   * @param end_position the position of the stroke end.
   */
  void HandleStrokeEnd(const glm::vec2& end_position);

  /**
   * Computes the angle that the cue makes to point at the cue ball.
   *
   * @param mouse_position current position of the mouse.
   * @return the angle between the cue and cue ball.
   */
  float ComputeCueAngle(const glm::vec2& mouse_position) const;

  /**
   * Computes the position and dimensions of the cue.
   *
   * @return Rectangle corresponding to cue dimensions.
   */
  ci::Rectf ComputeCueDimensions() const;

 private:
  Table* table_;
  Player player1_;
  Player player2_;
  Player* current_player;

  bool stroke_started_;
  glm::vec2 stroke_start_;
  float cue_pull_back_;
  bool is_red_on_;
  bool is_stroke_legal_;
  bool stroke_complete_;
};

}  // namespace snooker