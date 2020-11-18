/**
 * Created by Rishi Patel on 11/17/2020.
 */

#include "core/table.h"
#include "core/ball.h"
#include "core/table_cushion.h"
#include "cinder/gl/gl.h"
#include "catch2/catch.hpp"

using snooker::Ball;
using snooker::Table;
using snooker::TableCushion;
using snooker::StraightCushion;

/**
 * Testing strategy: test each function in the Ball class, including all
 * relevant edge cases.
 */

static const double kMarginOfError = 0.001;

TEST_CASE("Creating a Table.") {
  // Sanity check -- nothing to check via require statements.
  SECTION("Calling default constructor.") {
    Table table;
  }

  SECTION("Calling overloaded constructor.") {
    StraightCushion cushion1(ci::Rectf(100, 110, 115, 300));
    std::vector<TableCushion*> cushions{&cushion1};
    Table table(ci::Rectf(100, 100, 500, 500), cushions);

    REQUIRE(glm::vec2(100, 100) == table.GetWalls().getUpperLeft());
    REQUIRE(glm::vec2(500, 500) == table.GetWalls().getLowerRight());
    REQUIRE(1 == table.GetCushions().size());
  }
}

TEST_CASE("Validate adding Balls to the Table.") {
  StraightCushion cushion1(ci::Rectf(100, 110, 115, 300));
  std::vector<TableCushion*> cushions{&cushion1};
  Table table(ci::Rectf(100, 100, 500, 500), cushions);

  SECTION("Adding one Ball to an empty Table.") {
    table.AddBall(
        Ball(glm::vec2(300, 300), glm::vec2(60, 80), ci::Color("blue"), 1, 2));
    REQUIRE(1 == table.GetBalls().size());
    REQUIRE(glm::vec2(300, 300) == table.GetBalls()[0].GetPosition());
  }

  SECTION("Adding multiple Balls to a Table.") {
    table.AddBall(
        Ball(glm::vec2(300, 300), glm::vec2(60, 80), ci::Color("blue"), 1, 2));
    table.AddBall(
        Ball(glm::vec2(400, 300), glm::vec2(-4, 6), ci::Color("green"), 4, 5));
    REQUIRE(2 == table.GetBalls().size());
    REQUIRE(glm::vec2(300, 300) == table.GetBalls()[0].GetPosition());
    REQUIRE(glm::vec2(-0.04, 0.06) == table.GetBalls()[1].GetVelocity());
  }

  SECTION("Attempting to add Balls outside of the walls of a Table.") {
    table.AddBall(
        Ball(glm::vec2(300, 300), glm::vec2(60, 80), ci::Color("blue"), 1, 2));
    table.AddBall(
        Ball(glm::vec2(40, 300), glm::vec2(-4, 6), ci::Color("green"), 4, 5));
    REQUIRE(1 == table.GetBalls().size());
    REQUIRE(glm::vec2(300, 300) == table.GetBalls()[0].GetPosition());
  }
}