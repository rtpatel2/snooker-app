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
  /**
   * Creates a new GameEngine for the specified Table.
   * @param table Table associated with this GameEngine.
   */
  GameEngine(Table* table);

  /** Handles the logic behind pocketing Balls. */
  void PocketBalls();

  /**
   * Determines whether or not Player 1 is currently at the Table.
   *
   * @return true if Player 1 is at the table, and false otherwise.
   */
  bool IsPlayer1Turn() const;

  /**
   * Performs an automated stroke for the CPU, striking the nearest object
   * Ball of the correct color and attempting to pocket it optimally.
   */
  void PerformCPUStroke();

  /** Computes the best stroke for the CPU to perform. */
  void ComputeBestStroke();

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

  /**
   * Determines whether or not this game is over.
   *
   * @return true if the game is over, and false otherwise.
   */
  bool IsGameOver() const;

  const Player& GetPlayer1() const;
  const Player& GetPlayer2() const;
  const Player* GetCurrentPlayer() const;
  bool GetStrokeStarted() const;
  const glm::vec2& GetStrokeStartPosition() const;
  const glm::vec2& GetStrokeCurrentPosition() const;
  float GetCuePullBack() const;
  bool GetStrokeCompleted() const;

 private:
  /** Handles the logic behind ending a Player's stroke. */
  void EndStroke();

  Table* table_;
  Player player1_;
  Player player2_;
  Player* current_player_;

  bool stroke_started_;
  glm::vec2 stroke_start_position_;
  glm::vec2 stroke_current_position_;
  glm::vec2 stroke_end_position_;
  float cue_pull_back_;
  bool stroke_completed_;

  size_t red_ball_count_;
  ci::Color least_value_color_;
};

}  // namespace snooker