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
  StraightCushion left_cushion(ci::Rectf(100, 100, 110, 400));
  StraightCushion right_cushion(ci::Rectf(500, 100, 510, 400));
  StraightCushion upper_cushion(ci::Rectf(130, 100, 330, 110));
  StraightCushion lower_cushion(ci::Rectf(130, 490, 330, 500));

  SECTION("Collision with cushion to the left of the Ball.") {
    Ball ball(Ball(glm::vec2(111.2, 300), glm::vec2(-123, 456),
                   ci::Color("pink"), 8.6f, 3, 1));
    glm::vec2 exit_velocity = left_cushion.ComputeVelocityAfterCollision(ball);

    REQUIRE(1.168 == Approx(exit_velocity.x).margin(kMarginOfError));
    REQUIRE(4.560 == Approx(exit_velocity.y).margin(kMarginOfError));
  }

  SECTION("Collision with cushion to the right of the Ball.") {
    Ball ball(Ball(glm::vec2(499.2, 300), glm::vec2(123, -456),
                   ci::Color("blue"), 12, 13, 2));
    glm::vec2 exit_velocity = right_cushion.ComputeVelocityAfterCollision(ball);

    REQUIRE(-1.168 == Approx(exit_velocity.x).margin(kMarginOfError));
    REQUIRE(-4.560 == Approx(exit_velocity.y).margin(kMarginOfError));
  }

  SECTION("Collision with cushion above the Ball.") {
    Ball ball(Ball(glm::vec2(300, 103), glm::vec2(-54.3, -65),
                   ci::Color("green"), 4, 5, 3));
    glm::vec2 exit_velocity = upper_cushion.ComputeVelocityAfterCollision(ball);

    REQUIRE(-0.543 == Approx(exit_velocity.x).margin(kMarginOfError));
    REQUIRE(-0.650 == Approx(exit_velocity.y).margin(kMarginOfError));
  }

  SECTION("Collision with cushion below the Ball.") {
    Ball ball(Ball(glm::vec2(200, 489), glm::vec2(-23.3, 45),
                   ci::Color("green"), 4, 5, 4));
    glm::vec2 exit_velocity = lower_cushion.ComputeVelocityAfterCollision(ball);

    REQUIRE(-0.233 == Approx(exit_velocity.x).margin(kMarginOfError));
    REQUIRE(-0.427 == Approx(exit_velocity.y).margin(kMarginOfError));
  }

  SECTION("No change to velocity when there is no collision.") {
    Ball ball(Ball(glm::vec2(200, 389), glm::vec2(-23.3, 45),
                   ci::Color("green"), 4, 5, 5));
    glm::vec2 exit_velocity = lower_cushion.ComputeVelocityAfterCollision(ball);

    REQUIRE(-0.233 == Approx(exit_velocity.x).margin(kMarginOfError));
    REQUIRE(0.450 == Approx(exit_velocity.y).margin(kMarginOfError));
  }
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

  SECTION("Correctly computing new velocity when there is a collision.") {
    Ball ball(glm::vec2(102, 112), glm::vec2(-130, -34),
              ci::Color("white"), 5, 6, 6);
    glm::vec2 exit_velocity = cushion.ComputeVelocityAfterCollision(ball);

    REQUIRE(0.323 == Approx(exit_velocity.x).margin(kMarginOfError));
    REQUIRE(1.235 == Approx(exit_velocity.y).margin(kMarginOfError));
  }

  SECTION("No change to velocity when there is no collision.") {
    Ball ball(glm::vec2(152, 172), glm::vec2(-130, -34),
              ci::Color("white"), 5, 6, 7);
    glm::vec2 exit_velocity = cushion.ComputeVelocityAfterCollision(ball);

    REQUIRE(-1.300 == Approx(exit_velocity.x).margin(kMarginOfError));
    REQUIRE(-0.340 == Approx(exit_velocity.y).margin(kMarginOfError));
  }
}