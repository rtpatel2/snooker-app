/**
 * Created by Rishi Patel on 12/1/2020.
 */

#include "core/player.h"
#include "cinder/gl/gl.h"
#include "catch2/catch.hpp"

using snooker::Player;

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