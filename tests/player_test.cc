/**
 * Created by Rishi Patel on 12/1/2020.
 */

#include "core/player.h"
#include "core/table.h"
#include "cinder/gl/gl.h"
#include "catch2/catch.hpp"

using snooker::Player;
using snooker::Table;

/**
 * Testing strategy: test each function in the Player class, including all
 * relevant edge cases.
 */

TEST_CASE("Validate creating a Player.") {
  SECTION("Calling the constructor.") {
    Player player(true);
    REQUIRE(0 == player.GetBallsPocketedLastStroke().size());
    REQUIRE(player.IsCPUControlled());
  }
}

TEST_CASE("Validate determining if the ball-on is red.") {
  Table table;
  Player player(false);

  SECTION("Red balls still on the table, even stroke number.") {
    REQUIRE(player.IsBallOnRed(table.GetRedBallCount()));
  }

  SECTION("No red balls on the table, even stroke number.") {
    for (size_t ball_count = 0; ball_count < 15; ++ball_count) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    REQUIRE_FALSE(player.IsBallOnRed(table.GetRedBallCount()));
  }

  SECTION("Red balls still on the table, odd stroke number.") {
    for (size_t ball_count = 0; ball_count < 3; ++ball_count) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    player.EndStroke(true);
    REQUIRE_FALSE(player.IsBallOnRed(table.GetRedBallCount()));
  }

  SECTION("No red balls on the table, odd stroke number.") {
    for (size_t ball_count = 0; ball_count < 15; ++ball_count) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    player.EndStroke(true);
    REQUIRE_FALSE(player.IsBallOnRed(table.GetRedBallCount()));
  }
}

TEST_CASE("Validate determining if a stroke is legal.") {
  Table table;
  Player player(false);

  SECTION("Stroke in which no Ball is struck is illegal.") {
    REQUIRE_FALSE(player.IsStrokeLegal(
        table.GetRedBallCount(), table.GetLeastPointValueColor(),
        table.GetBalls().back().GetFirstContacted()));
  }

  // The following sections apply to cases when the ball-on is red.

  SECTION("Stroke in which first contacted Ball is not red is illegal.") {
    table.SetCueBallFirstContacted(table.GetBalls()[1].GetColor());
    table.SetCueBallFirstContacted(ci::Color("orange"));
    REQUIRE_FALSE(player.IsStrokeLegal(
        table.GetRedBallCount(), table.GetLeastPointValueColor(),
        table.GetBalls().back().GetFirstContacted()));
  }

  SECTION("Pocketing the cue Ball is illegal.") {
    player.AddBallPocketedLastStroke(table.GetBalls().back());
    REQUIRE_FALSE(player.IsStrokeLegal(
        table.GetRedBallCount(), table.GetLeastPointValueColor(),
        table.GetBalls().back().GetFirstContacted()));
  }

  SECTION("Pocketing any non-red Ball is illegal.") {
    table.SetCueBallFirstContacted(table.GetBalls()[20].GetColor());
    player.AddBallPocketedLastStroke(table.GetBalls()[20]);
    REQUIRE_FALSE(player.IsStrokeLegal(
        table.GetRedBallCount(), table.GetLeastPointValueColor(),
        table.GetBalls().back().GetFirstContacted()));
  }

  SECTION("Pocketing one red Ball is legal.") {
    table.SetCueBallFirstContacted(table.GetBalls()[1].GetColor());
    player.AddBallPocketedLastStroke(table.GetBalls()[1]);
    REQUIRE(player.IsStrokeLegal(table.GetRedBallCount(),
                                 table.GetLeastPointValueColor(),
                                 table.GetBalls().back().GetFirstContacted()));
  }

  SECTION("Pocketing multiple red Balls is legal.") {
    table.SetCueBallFirstContacted(table.GetBalls()[3].GetColor());
    player.AddBallPocketedLastStroke(table.GetBalls()[3]);
    player.AddBallPocketedLastStroke(table.GetBalls()[5]);
    player.AddBallPocketedLastStroke(table.GetBalls()[7]);
    REQUIRE(player.IsStrokeLegal(table.GetRedBallCount(),
                                 table.GetLeastPointValueColor(),
                                 table.GetBalls().back().GetFirstContacted()));
  }

  // The following sections apply to cases when the ball-on is colored.

  SECTION("Pocketing multiple colors is illegal.") {
    player.EndStroke(true);
    table.SetCueBallFirstContacted(ci::Color("black"));
    player.AddBallPocketedLastStroke(table.GetBalls()[20]);
    player.AddBallPocketedLastStroke(table.GetBalls()[19]);
    REQUIRE_FALSE(player.IsStrokeLegal(
        table.GetRedBallCount(), table.GetLeastPointValueColor(),
        table.GetBalls().back().GetFirstContacted()));
  }

  SECTION("Pocketing a color different from the first contacted is illegal.") {
    player.EndStroke(true);
    table.SetCueBallFirstContacted(ci::Color("green"));
    player.AddBallPocketedLastStroke(table.GetBalls()[18]);
    REQUIRE_FALSE(player.IsStrokeLegal(
        table.GetRedBallCount(), table.GetLeastPointValueColor(),
        table.GetBalls().back().GetFirstContacted()));
  }

  SECTION("Pocketing the cue ball is illegal.") {
    player.EndStroke(true);
    table.SetCueBallFirstContacted(ci::Color("brown"));
    player.AddBallPocketedLastStroke(table.GetBalls().back());
    REQUIRE_FALSE(player.IsStrokeLegal(
        table.GetRedBallCount(), table.GetLeastPointValueColor(),
        table.GetBalls().back().GetFirstContacted()));
  }

  SECTION("First contacting a red ball is illegal.") {
    player.EndStroke(true);
    table.SetCueBallFirstContacted(ci::Color("red"));
    REQUIRE_FALSE(player.IsStrokeLegal(
        table.GetRedBallCount(), table.GetLeastPointValueColor(),
        table.GetBalls().back().GetFirstContacted()));
  }

  SECTION(
      "First contacting any ball other than lowest point value color when "
      "no reds remain is illegal.") {
    player.EndStroke(true);
    for (size_t ball_to_remove = 0; ball_to_remove < 15; ++ball_to_remove) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    table.SetCueBallFirstContacted(ci::Color("pink"));
    REQUIRE_FALSE(player.IsStrokeLegal(
        table.GetRedBallCount(), table.GetLeastPointValueColor(),
        table.GetBalls().back().GetFirstContacted()));
  }

  SECTION("Pocketing any color is legal while reds are still on the table.") {
    player.EndStroke(true);
    table.SetCueBallFirstContacted(ci::Color("black"));
    player.AddBallPocketedLastStroke(table.GetBalls()[20]);
    REQUIRE(player.IsStrokeLegal(table.GetRedBallCount(),
                                 table.GetLeastPointValueColor(),
                                 table.GetBalls().back().GetFirstContacted()));
  }

  SECTION("Must contact yellow first when no reds are on the table.") {
    player.EndStroke(true);
    for (size_t i = 0; i < 15; ++i) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    table.SetCueBallFirstContacted(ci::Color("yellow"));
    REQUIRE(player.IsStrokeLegal(table.GetRedBallCount(),
                                 table.GetLeastPointValueColor(),
                                 table.GetBalls().back().GetFirstContacted()));
  }

  SECTION("Must pocket pink when all lower point value Balls are pocketed.") {
    player.EndStroke(true);
    for (size_t i = 0; i < 19; ++i) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    table.SetCueBallFirstContacted(ci::Color("pink"));
    player.AddBallPocketedLastStroke(table.GetBalls().front());
    REQUIRE(player.IsStrokeLegal(table.GetRedBallCount(),
                                 table.GetLeastPointValueColor(),
                                 table.GetBalls().back().GetFirstContacted()));
  }
}

TEST_CASE("Validate adding Balls pocketed last stroke.") {
  Player player(true);
  Table table;

  SECTION("Pocketing one Ball.") {
    player.AddBallPocketedLastStroke(table.GetBalls().front());
    REQUIRE(1 == player.GetBallsPocketedLastStroke().size());
    REQUIRE(ci::Color("red") ==
            player.GetBallsPocketedLastStroke().front()
                                    .GetColor());
  }

  SECTION("Pocketing multiple Balls.") {
    player.AddBallPocketedLastStroke(table.GetBalls().front());
    table.RemoveBallFromTable(table.GetBalls().front());
    player.AddBallPocketedLastStroke(table.GetBalls().back());
    table.RemoveBallFromTable(table.GetBalls().back());
    player.AddBallPocketedLastStroke(table.GetBalls().back());
    table.RemoveBallFromTable(table.GetBalls().back());

    REQUIRE(3 == player.GetBallsPocketedLastStroke().size());
    REQUIRE(ci::Color("red") ==
            player.GetBallsPocketedLastStroke()[0].GetColor());
    REQUIRE(ci::Color("white") ==
            player.GetBallsPocketedLastStroke()[1].GetColor());
    REQUIRE(ci::Color("black") ==
            player.GetBallsPocketedLastStroke()[2].GetColor());
  }
}

TEST_CASE("Validate ending a stroke.") {
  Player player(false);
  Table table;

  SECTION("Ending a stroke and leaving the table.") {
    player.EndStroke(false);
    REQUIRE(0 == player.GetStrokeNumber());
    REQUIRE(0 == player.GetBallsPocketedLastStroke().size());
  }

  SECTION("Ending a stroke but staying at the table.") {
    player.EndStroke(false);
    player.EndStroke(true);
    player.EndStroke(true);
    REQUIRE(2 == player.GetStrokeNumber());
    REQUIRE(0 == player.GetBallsPocketedLastStroke().size());
  }
}

TEST_CASE("Validate adding points to a player.") {
  Player player1(false);
  Player player2(true);

  SECTION("Adding points to a player for the first time.") {
    player1.AddPoints(13);
    REQUIRE(13 == player1.GetScore());
    REQUIRE(0 == player2.GetScore());
  }

  SECTION("Adding points to a player multiple times.") {
    player2.AddPoints(1);
    player2.AddPoints(6);
    REQUIRE(0 == player1.GetScore());
    REQUIRE(7 == player2.GetScore());
  }

  SECTION("Adding points to multiple players.") {
    player1.AddPoints(1);
    player1.AddPoints(2);
    player1.AddPoints(1);
    player2.AddPoints(1);
    player2.AddPoints(7);
    REQUIRE(4 == player1.GetScore());
    REQUIRE(8 == player2.GetScore());
  }
}