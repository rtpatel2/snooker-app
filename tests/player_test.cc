/**
 * Created by Rishi Patel on 12/1/2020.
 */

#include "core/player.h"
#include "core/player.h"
#include "cinder/gl/gl.h"
#include "catch2/catch.hpp"

using snooker::Player;
using snooker::Table;

/**
 * Testing strategy: test each function in the Player class, including all
 * relevant edge cases.
 */

static const double kMarginOfError = 0.001;

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
    
  }

  SECTION("Pocketing the cue Ball is illegal.") {

  }

  SECTION("Pocketing any non-red Ball is illegal.") {

  }

  SECTION("Pocketing one red Ball is legal.") {

  }

  SECTION("Pocketing multiple red Balls is legal.") {

  }

  // The following sections apply to cases when the ball-on is colored.

  SECTION("Pocketing multiple colors is illegal.") {

  }

  SECTION("Pocketing a color different from the first contacted is illegal.") {

  }

  SECTION("Pocketing the cue ball is illegal.") {

  }

  SECTION("First contacting a red ball is illegal.") {

  }

  SECTION("First contacting any ball other than lowest point value color when "
      "no reds remain is illegal.") {

  }
}