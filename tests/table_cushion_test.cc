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

}