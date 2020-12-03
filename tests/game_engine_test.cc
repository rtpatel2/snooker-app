/**
 * Created by Rishi Patel on 12/1/2020.
 */

#include "core/game_engine.h"
#include "core/table.h"
#include "core/ball.h"
#include "catch2/catch.hpp"

using snooker::GameEngine;
using snooker::Table;
using snooker::Ball;

/**
 * Testing strategy: test each function in the GameEngine class, including all
 * relevant edge cases.
 */

TEST_CASE("Validate creating a GameEngine") {
  SECTION("Calling the constructor.") {
    Table table;
    GameEngine engine(&table);
    REQUIRE_FALSE(engine.GetStrokeStarted());
    REQUIRE(0 == engine.GetCuePullBack());
    REQUIRE_FALSE(engine.GetStrokeCompleted());
  }
}

TEST_CASE("Validate pocketing Balls.") {
  Table table;
  GameEngine engine(&table);

  SECTION("Pocketing one red Ball.") {
    engine.HandleStrokeStart(glm::vec2(100, 100));
    engine.HandleStrokeEnd(glm::vec2(100, 100));
    table.AddBall(Ball(glm::vec2(113, 113), glm::vec2(-40, -50), ci::Color
                       ("red"),
                       5, 5, 3));
    table.SetCueBallFirstContacted(ci::Color("red"));
    REQUIRE(23 == table.GetBalls().size());
    engine.PocketBalls();
    REQUIRE(22 == table.GetBalls().size());
    REQUIRE(1 == engine.GetPlayer1().GetStrokeNumber());
    REQUIRE(0 == engine.GetPlayer2().GetStrokeNumber());
    REQUIRE(&(engine.GetPlayer1()) == engine.GetCurrentPlayer());
  }

  SECTION("Pocketing multiple red Balls.") {
    engine.HandleStrokeStart(glm::vec2(500, 500));
    engine.HandleStrokeEnd(glm::vec2(500, 500));
    engine.PocketBalls();

    engine.HandleStrokeStart(glm::vec2(300, 350));
    engine.HandleStrokeEnd(glm::vec2(300, 350));
    table.AddBall(Ball(glm::vec2(110, 110), glm::vec2(-40, -50),
                       ci::Color("red"), 5, 5, 1));
    table.AddBall(
        Ball(glm::vec2(113, 531), glm::vec2(-7, 0), ci::Color("red"), 5, 5, 1));
    table.AddBall(
        Ball(glm::vec2(979, 531), glm::vec2(0, 0), ci::Color("red"), 5, 5, 1));
    table.SetCueBallFirstContacted(ci::Color("red"));
    REQUIRE(25 == table.GetBalls().size());
    engine.PocketBalls();
    REQUIRE(22 == table.GetBalls().size());
    REQUIRE(0 == engine.GetPlayer1().GetStrokeNumber());
    REQUIRE(1 == engine.GetPlayer2().GetStrokeNumber());
    REQUIRE(&(engine.GetPlayer2()) == engine.GetCurrentPlayer());
  }

  SECTION("Pocketing a red and then a color.") {
    engine.HandleStrokeStart(glm::vec2(500, 500));
    engine.HandleStrokeEnd(glm::vec2(500, 500));
    table.AddBall(Ball(glm::vec2(110, 110), glm::vec2(-40, -50),
                       ci::Color("red"), 5, 5, 1));
    table.SetCueBallFirstContacted(ci::Color("red"));
    REQUIRE(23 == table.GetBalls().size());
    engine.PocketBalls();
    REQUIRE(22 == table.GetBalls().size());
    REQUIRE(1 == engine.GetPlayer1().GetStrokeNumber());
    REQUIRE(0 == engine.GetPlayer2().GetStrokeNumber());
    REQUIRE(&(engine.GetPlayer1()) == engine.GetCurrentPlayer());

    engine.HandleStrokeStart(glm::vec2(500, 500));
    engine.HandleStrokeEnd(glm::vec2(500, 500));
    table.AddBall(Ball(glm::vec2(110, 110), glm::vec2(-40, -50),
                       ci::Color("black"), 5, 5, 1));
    table.SetCueBallFirstContacted(ci::Color("black"));
    REQUIRE(23 == table.GetBalls().size());
    engine.PocketBalls();
    REQUIRE(23 == table.GetBalls().size());
    REQUIRE(2 == engine.GetPlayer1().GetStrokeNumber());
    REQUIRE(0 == engine.GetPlayer2().GetStrokeNumber());
    REQUIRE(&(engine.GetPlayer1()) == engine.GetCurrentPlayer());
  }

  SECTION("Pocketing colors when no reds are on the Table.") {
    for (size_t ball_to_remove = 0; ball_to_remove < 15; ++ball_to_remove) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    engine.HandleStrokeStart(glm::vec2(500, 500));
    engine.HandleStrokeEnd(glm::vec2(500, 500));
    table.AddBall(Ball(glm::vec2(546, 110), glm::vec2(-40, -50),
                       ci::Color("yellow"), 5, 5, 1));
    table.SetCueBallFirstContacted(ci::Color("yellow"));
    REQUIRE(8 == table.GetBalls().size());
    engine.PocketBalls();
    REQUIRE(7 == table.GetBalls().size());
    REQUIRE(1 == engine.GetPlayer1().GetStrokeNumber());
    REQUIRE(0 == engine.GetPlayer2().GetStrokeNumber());
    REQUIRE(&(engine.GetPlayer1()) == engine.GetCurrentPlayer());
  }
}

TEST_CASE("Validate starting a stroke.") {
  Table table;
  GameEngine engine(&table);

  SECTION("Starting a stroke when the Table is steady.") {
    engine.HandleStrokeStart(glm::vec2(123, 456));

    REQUIRE(engine.GetStrokeStarted());
    REQUIRE(glm::vec2(123, 456) == engine.GetStrokeStartPosition());
  }

  SECTION("Attempting to start a stroke when the Table is not steady.") {
    table.SetCueBallVelocity(glm::vec2(1, 2));
    engine.HandleStrokeStart(glm::vec2(500, 400));

    REQUIRE_FALSE(engine.GetStrokeStarted());
  }
}