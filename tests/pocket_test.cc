/**
 * Created by Rishi Patel on 12/1/2020.
 */

#include "core/pocket.h"
#include "core/ball.h"
#include "cinder/gl/gl.h"
#include "catch2/catch.hpp"

using snooker::Pocket;
using snooker::Ball;

/**
 * Testing strategy: test each function in the Pocket class, including all
 * relevant edge cases.
 */

TEST_CASE("Validate creating a Pocket.") {
  SECTION("Calling the constructor.") {
    Pocket pocket(glm::vec2(500, 500), 15, ci::Color("black"));
    REQUIRE(glm::vec2(500, 500) == pocket.GetPosition());
    REQUIRE(15 == pocket.GetRadius());
    REQUIRE(ci::Color("black") == pocket.GetColor());
  }
}

TEST_CASE("Validate determining whether or not a Ball is pocketed.") {
  Pocket pocket(glm::vec2(500, 500), 15, ci::Color("black"));
  Ball ball1(glm::vec2(100, 100), glm::vec2(5, 5), ci::Color("white"), 5, 2, 3);
  Ball ball2(glm::vec2(496.5, 500), glm::vec2(3, 3), ci::Color(), 7, 34, 1);

  SECTION("Identify a Ball outside of the Pocket as not pocketed.") {
    REQUIRE_FALSE(pocket.IsPocketed(ball1));
  }

  SECTION("Identify a Ball inside the Pocket as pocketed.") {
    REQUIRE(pocket.IsPocketed(ball2));
  }
}