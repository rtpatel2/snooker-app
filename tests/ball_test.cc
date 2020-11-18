/**
 * Created by Rishi Patel on 11/14/2020.
 */

#include "core/ball.h"
#include "cinder/gl/gl.h"
#include "catch2/catch.hpp"

using snooker::Ball;

/**
 * Testing strategy: test each function in the Ball class, including all
 * relevant edge cases.
 */

static const double kMarginOfError = 0.001;

TEST_CASE("Creating a Ball.") {
  SECTION("Calling the constructor.") {
    Ball ball(glm::vec2(300, 400), glm::vec2(-1.2, 3.4), ci::Color("red"),
              12.3f, 4.3f);
    REQUIRE(glm::vec2(300, 400) == ball.GetPosition());
    REQUIRE(glm::vec2(-1.2, 3.4) == ball.GetVelocity());
    REQUIRE(ci::Color("red") == ball.GetColor());
    REQUIRE(12.3 == ball.GetRadius());
    REQUIRE(4.3 == ball.GetMass());
  }
}