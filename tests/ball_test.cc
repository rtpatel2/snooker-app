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
    REQUIRE(glm::vec2(-0.012, 0.034) == ball.GetVelocity());
    REQUIRE(ci::Color("red") == ball.GetColor());
    REQUIRE(12.3f == ball.GetRadius());
    REQUIRE(4.3f == ball.GetMass());
  }
}

TEST_CASE("Validate updating a Ball's position.") {
  SECTION("Ball with non-zero velocity components.") {
    Ball ball(glm::vec2(100, 100), glm::vec2(40, 30), ci::Color("white"), 1, 1);
    ball.UpdatePosition();
    REQUIRE(0.3608 == Approx(ball.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0.2706 == Approx(ball.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(100.3608 == Approx(ball.GetPosition().x).margin(kMarginOfError));
    REQUIRE(100.2706 == Approx(ball.GetPosition().y).margin(kMarginOfError));
  }

  SECTION("Ball with one non-zero velocity component.") {
    Ball ball(glm::vec2(100, 100), glm::vec2(0, -300), ci::Color("white"), 1,
              1);
    ball.UpdatePosition();
    REQUIRE(0 == Approx(ball.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(-2.951 == Approx(ball.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(100 == Approx(ball.GetPosition().x).margin(kMarginOfError));
    REQUIRE(97.049 == Approx(ball.GetPosition().y).margin(kMarginOfError));
  }

  SECTION("Ball with zero speed.") {
    Ball ball(glm::vec2(345, 677), glm::vec2(0, 0), ci::Color("white"), 1, 1);
    ball.UpdatePosition();
    REQUIRE(0 == Approx(ball.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(345 == Approx(ball.GetPosition().x).margin(kMarginOfError));
    REQUIRE(677 == Approx(ball.GetPosition().y).margin(kMarginOfError));
  }

  SECTION("Ball coming to a stop due to friction.") {
    Ball ball(glm::vec2(300, 400), glm::vec2(-1.2, 3.4), ci::Color("red"),
              12.3f, 4.3f);
    ball.UpdatePosition();
    REQUIRE(0 == Approx(ball.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(300 == Approx(ball.GetPosition().x).margin(kMarginOfError));
    REQUIRE(400 == Approx(ball.GetPosition().y).margin(kMarginOfError));
  }
}

TEST_CASE("Validate computing velocity after collision with another Ball.") {
  SECTION("")
}