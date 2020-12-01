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
    Player player;
    REQUIRE(0 == player.GetBallsPottedLastStroke().size());
  }
}

TEST_CASE("Validate determining if a stroke is legal.") {
  Table table;
  Player player;

  SECTION("Stroke in which no Ball is struck is illegal.") {
    REQUIRE_FALSE(player.IsStrokeLegal(table));
  }

  // The following sections apply to cases when the ball-on is red.

  SECTION("Stroke in which first contacted Ball is not red is illegal.") {
    table.SetCueBallFirstContacted(table.GetBalls()[1].GetColor());
    table.SetCueBallFirstContacted(ci::Color("orange"));
    REQUIRE_FALSE(player.IsStrokeLegal(table));
  }

  SECTION("Pocketing the cue Ball is illegal.") {
    player.AddBallsPottedLastStroke(table.GetBalls().back());
    REQUIRE_FALSE(player.IsStrokeLegal(table));
  }

  SECTION("Pocketing any non-red Ball is illegal.") {
    table.SetCueBallFirstContacted(table.GetBalls()[20].GetColor());
    player.AddBallsPottedLastStroke(table.GetBalls()[20]);
    REQUIRE_FALSE(player.IsStrokeLegal(table));
  }

  SECTION("Pocketing one red Ball is legal.") {
    table.SetCueBallFirstContacted(table.GetBalls()[1].GetColor());
    player.AddBallsPottedLastStroke(table.GetBalls()[1]);
    REQUIRE(player.IsStrokeLegal(table));
  }

  SECTION("Pocketing multiple red Balls is legal.") {
    table.SetCueBallFirstContacted(table.GetBalls()[3].GetColor());
    player.AddBallsPottedLastStroke(table.GetBalls()[3]);
    player.AddBallsPottedLastStroke(table.GetBalls()[5]);
    player.AddBallsPottedLastStroke(table.GetBalls()[7]);
    REQUIRE(player.IsStrokeLegal(table));
  }

  // The following sections apply to cases when the ball-on is colored.

  SECTION("Pocketing multiple colors is illegal.") {
    player.EndStroke(true);
    table.SetCueBallFirstContacted(ci::Color("black"));
    player.AddBallsPottedLastStroke(table.GetBalls()[20]);
    player.AddBallsPottedLastStroke(table.GetBalls()[19]);
    REQUIRE_FALSE(player.IsStrokeLegal(table));
  }

  SECTION("Pocketing a color different from the first contacted is illegal.") {
    player.EndStroke(true);
    table.SetCueBallFirstContacted(ci::Color("green"));
    player.AddBallsPottedLastStroke(table.GetBalls()[18]);
    REQUIRE_FALSE(player.IsStrokeLegal(table));
  }

  SECTION("Pocketing the cue ball is illegal.") {
    player.EndStroke(true);
    table.SetCueBallFirstContacted(ci::Color("brown"));
    player.AddBallsPottedLastStroke(table.GetBalls().back());
    REQUIRE_FALSE(player.IsStrokeLegal(table));
  }

  SECTION("First contacting a red ball is illegal.") {
    player.EndStroke(true);
    table.SetCueBallFirstContacted(ci::Color("red"));
    REQUIRE_FALSE(player.IsStrokeLegal(table));
  }

  SECTION("First contacting any ball other than lowest point value color when "
      "no reds remain is illegal.") {
    player.EndStroke(true);
    for (size_t i = 0; i < 15; ++i) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    table.SetCueBallFirstContacted(ci::Color("pink"));
    REQUIRE_FALSE(player.IsStrokeLegal(table));
  }

  SECTION("Pocketing any color is legal while reds are still on the table.") {
    player.EndStroke(true);
    table.SetCueBallFirstContacted(ci::Color("black"));
    player.AddBallsPottedLastStroke(table.GetBalls()[20]);
    REQUIRE(player.IsStrokeLegal(table));
  }

  SECTION("Must contact yellow first when no reds are on the table.") {
    player.EndStroke(true);
    for (size_t i = 0; i < 15; ++i) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    table.SetCueBallFirstContacted(ci::Color("yellow"));
    REQUIRE(player.IsStrokeLegal(table));
  }

  SECTION("Must pocket pink when all lower point value Balls are pocketed.") {
    player.EndStroke(true);
    for (size_t i = 0; i < 19; ++i) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    table.SetCueBallFirstContacted(ci::Color("pink"));
    player.AddBallsPottedLastStroke(table.GetBalls().front());
    REQUIRE(player.IsStrokeLegal(table));
  }
}

TEST_CASE("Validate adding Balls pocketed last stroke.") {
  Player player;
  Table table;

  SECTION("Pocketing one Ball.") {
    player.AddBallsPottedLastStroke(table.GetBalls().front());
    REQUIRE(1 == player.GetBallsPottedLastStroke().size());
    REQUIRE(ci::Color("red") == player.GetBallsPottedLastStroke().front()
                                    .GetColor());
  }

  SECTION("Pocketing multiple Balls.") {
    player.AddBallsPottedLastStroke(table.GetBalls().front());
    table.RemoveBallFromTable(table.GetBalls().front());
    player.AddBallsPottedLastStroke(table.GetBalls().back());
    table.RemoveBallFromTable(table.GetBalls().back());
    player.AddBallsPottedLastStroke(table.GetBalls().back());
    table.RemoveBallFromTable(table.GetBalls().back());

    REQUIRE(3 == player.GetBallsPottedLastStroke().size());
    REQUIRE(ci::Color("red") ==
            player.GetBallsPottedLastStroke()[0].GetColor());
    REQUIRE(ci::Color("white") ==
            player.GetBallsPottedLastStroke()[1].GetColor());
    REQUIRE(ci::Color("black") ==
            player.GetBallsPottedLastStroke()[2].GetColor());
  }
}

TEST_CASE("Validate ending a stroke.") {
  Player player;
  Table table;

  SECTION("Ending a stroke and leaving the table.") {
    player.EndStroke(false);
    REQUIRE(0 == player.GetStrokeNumber());
    REQUIRE(0 == player.GetBallsPottedLastStroke().size());
  }

  SECTION("Ending a stroke but staying at the table.") {
    player.EndStroke(false);
    player.EndStroke(true);
    player.EndStroke(true);
    REQUIRE(2 == player.GetStrokeNumber());
    REQUIRE(0 == player.GetBallsPottedLastStroke().size());
  }
}