/**
 * Created by Rishi Patel on 11/17/2020.
 */

#include "core/table_cushion.h"
#include "core/table.h"
#include "core/ball.h"
#include "cinder/gl/gl.h"
#include "catch2/catch.hpp"

using snooker::Ball;
using snooker::Table;
using snooker::TableCushion;
using snooker::StraightCushion;
using snooker::CurvedCushion;

/**
 * Testing strategy: test each function in the Ball class, including all
 * relevant edge cases.
 */

static const double kMarginOfError = 0.001;

TEST_CASE("Creating a StraightCushion.") {
  SECTION("Calling the constructor.") {
    StraightCushion cushion(ci::Rectf(10, 10, 100, 100));
    REQUIRE(glm::vec2(10, 10) == cushion.GetBounds().getUpperLeft());
    REQUIRE(glm::vec2(100, 100) == cushion.GetBounds().getLowerRight());
  }
}

TEST_CASE("Validate computing velocity of Ball after collision with "
    "StraightCushion.") {
  StraightCushion cushion(ci::Rectf(130, 490, 330, 500));
  Ball ball(Ball(glm::vec2(200, 489), glm::vec2(-23.3, 45), ci::Color("green"),
                 4, 5));
  glm::vec2 exit_velocity = cushion.ComputeVelocityAfterCollision(ball);

  REQUIRE(-0.233 == Approx(exit_velocity.x).margin(kMarginOfError));
  REQUIRE(-0.427 == Approx(exit_velocity.y).margin(kMarginOfError));
}

TEST_CASE("Creating a CurvedCushion.") {
  SECTION("Calling the constructor.") {
    CurvedCushion cushion(glm::vec2(500, 500), 15);
    REQUIRE(glm::vec2(500, 500) == cushion.GetPosition());
    REQUIRE(15 == cushion.GetRadius());
  }
}

TEST_CASE("Validate computing velocity of Ball after collision with "
          "CurvedCushion.") {
  CurvedCushion cushion(glm::vec2(100, 110), 15);
  Ball ball(glm::vec2(102, 112), glm::vec2(-130, -34),
                     ci::Color("white"), 5, 6);
  glm::vec2 exit_velocity = cushion.ComputeVelocityAfterCollision(ball);

  REQUIRE(0.323 == Approx(exit_velocity.x).margin(kMarginOfError));
  REQUIRE(1.235 == Approx(exit_velocity.y).margin(kMarginOfError));
}