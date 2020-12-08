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

static const double kMarginOfError = 0.001;

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

TEST_CASE("Validate checking if Player 1 is currently at the Table.") {
  Table table;
  GameEngine engine(&table);

  SECTION("Player 1 is at the Table.") {
    REQUIRE(engine.IsPlayer1Turn());
  }

  SECTION("Player 2 is at the Table.") {
    engine.HandleStrokeStart(glm::vec2(100, 100));
    engine.HandleStrokeEnd(glm::vec2(100, 100));
    engine.PocketBalls();

    REQUIRE_FALSE(engine.IsPlayer1Turn());
  }
}

TEST_CASE("Validate CPU performing a stroke.") {
  Table table;
  GameEngine engine(&table);

  SECTION("CPU starting a stroke.") {
    REQUIRE_FALSE(engine.GetStrokeStarted());
    engine.PerformCPUStroke();
    REQUIRE(engine.GetStrokeStarted());
    REQUIRE(198.838 ==
            Approx(engine.GetStrokeEndPosition().x).margin(kMarginOfError));
    REQUIRE(361.469 ==
            Approx(engine.GetStrokeEndPosition().y).margin(kMarginOfError));
  }

  SECTION("CPU pulling back cue.") {
    engine.PerformCPUStroke();
    REQUIRE(engine.GetStrokeStartPosition() ==
            engine.GetStrokeCurrentPosition());
    for (size_t pull_back = 0; pull_back < 25; ++pull_back) {
      engine.PerformCPUStroke();
    }
    REQUIRE(223.794 ==
            Approx(engine.GetStrokeCurrentPosition().x).margin(kMarginOfError));
    REQUIRE(359.985 ==
            Approx(engine.GetStrokeCurrentPosition().y).margin(kMarginOfError));

    for (size_t pull_back = 0; pull_back < 25; ++pull_back) {
      engine.PerformCPUStroke();
    }
    REQUIRE(engine.GetStrokeEndPosition().x ==
            Approx(engine.GetStrokeCurrentPosition().x).margin(kMarginOfError));
    REQUIRE(engine.GetStrokeEndPosition().y ==
            Approx(engine.GetStrokeCurrentPosition().y).margin(kMarginOfError));
  }

  SECTION("CPU ending a stroke.") {
    engine.PerformCPUStroke();
    for (size_t pull_back = 0; pull_back < 50; ++pull_back) {
      engine.PerformCPUStroke();
    }

    REQUIRE(engine.GetStrokeStarted());
    REQUIRE_FALSE(engine.GetStrokeCompleted());
    engine.PerformCPUStroke();
    REQUIRE_FALSE(engine.GetStrokeStarted());
    REQUIRE(0 == engine.GetCuePullBack());
    REQUIRE(engine.GetStrokeCompleted());
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

TEST_CASE("Validate pulling back the cue.") {
  Table table;
  GameEngine engine(&table);

  SECTION("Pulling back the cue less than the maximum.") {
    engine.HandleStrokeStart(glm::vec2(100, 100));
    engine.HandleCuePullBack(glm::vec2(105, 100));
    REQUIRE(5 == engine.GetCuePullBack());
  }

  SECTION("Pulling back the cue more than the maximum.") {
    engine.HandleStrokeStart(glm::vec2(100, 100));
    engine.HandleCuePullBack(glm::vec2(105, 300));
    REQUIRE(50 == engine.GetCuePullBack());
  }
}

TEST_CASE("Validate releasing the cue and ending a stroke.") {
  Table table;
  GameEngine engine(&table);

  SECTION("Ending a stroke of zero pull-back.") {
    engine.HandleStrokeStart(glm::vec2(200, 200));
    engine.HandleStrokeEnd(glm::vec2(200, 200));

    REQUIRE(glm::vec2(0, 0) == table.GetBalls().back().GetVelocity());
  }

  SECTION("Ending a stroke of non-zero pull-back.") {
    engine.HandleStrokeStart(glm::vec2(200, 200));
    engine.HandleStrokeEnd(glm::vec2(203, 204));

    REQUIRE(-0.45 ==
        Approx(table.GetBalls().back().GetVelocity().x).margin(kMarginOfError));
    REQUIRE(-0.6 ==
        Approx(table.GetBalls().back().GetVelocity().y).margin(kMarginOfError));
  }
}

TEST_CASE("Validate computing the cue angle.") {
  Table table;
  GameEngine engine(&table);

  SECTION("Angle in the first quadrant.") {
    REQUIRE(0.7509 == Approx(engine.ComputeCueAngle(glm::vec2(245, 355)))
                      .margin(kMarginOfError));
  }

  SECTION("Angle in the second quadrant.") {
    REQUIRE(1.914 == Approx(engine.ComputeCueAngle(glm::vec2(250, 355)))
                      .margin(kMarginOfError));
  }

  SECTION("Angle in the third quadrant.") {
    REQUIRE(4.0177 == Approx(engine.ComputeCueAngle(glm::vec2(250, 360)))
                          .margin(kMarginOfError));
  }

  SECTION("Angle in the fourth quadrant.") {
    REQUIRE(-0.3805 == Approx(engine.ComputeCueAngle(glm::vec2(245, 360)))
                           .margin(kMarginOfError));
  }

  SECTION("0 degree angle.") {
    REQUIRE(0 == Approx(engine.ComputeCueAngle(glm::vec2(240, 358.5)))
        .margin(kMarginOfError));
  }

  SECTION("90 degree angle.") {
    REQUIRE(1.5708 == Approx(engine.ComputeCueAngle(glm::vec2(248.75, 330)))
        .margin(kMarginOfError));
  }

  SECTION("180 degree angle.") {
    REQUIRE(3.1416 == Approx(engine.ComputeCueAngle(glm::vec2(260, 358.5)))
        .margin(kMarginOfError));
  }

  SECTION("270 degree angle.") {
    REQUIRE(-1.5708 == Approx(engine.ComputeCueAngle(glm::vec2(248.75, 370)))
        .margin(kMarginOfError));
  }
}

TEST_CASE("Validate computing cue dimensions.") {
  Table table;
  GameEngine engine(&table);

  SECTION("Computing dimensions without pulling back cue.") {
    engine.HandleStrokeStart(glm::vec2(100, 100));
    engine.HandleCuePullBack(glm::vec2(103, 104));
    REQUIRE(-255 ==
            Approx(engine.ComputeCueDimensions().x1).margin(kMarginOfError));
    REQUIRE(-2.5 ==
            Approx(engine.ComputeCueDimensions().y1).margin(kMarginOfError));
    REQUIRE(-11.563 ==
            Approx(engine.ComputeCueDimensions().x2).margin(kMarginOfError));
    REQUIRE(2.5 ==
            Approx(engine.ComputeCueDimensions().y2).margin(kMarginOfError));
  }

  SECTION("Computing dimensions with cue pull-back.") {
    REQUIRE(-250 ==
            Approx(engine.ComputeCueDimensions().x1).margin(kMarginOfError));
    REQUIRE(-2.5 ==
            Approx(engine.ComputeCueDimensions().y1).margin(kMarginOfError));
    REQUIRE(-6.563 ==
            Approx(engine.ComputeCueDimensions().x2).margin(kMarginOfError));
    REQUIRE(2.5 ==
            Approx(engine.ComputeCueDimensions().y2).margin(kMarginOfError));
  }
}

TEST_CASE("Validate determining if a game is over.") {
  Table table;
  GameEngine engine(&table);

  SECTION("Identify a complete game as being over.") {
    for (size_t ball_count = 0; ball_count < 21; ++ball_count) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    REQUIRE(engine.IsGameOver());
  }

  SECTION("Identify an incomplete game as not being over.") {
    REQUIRE_FALSE(engine.IsGameOver());
  }
}