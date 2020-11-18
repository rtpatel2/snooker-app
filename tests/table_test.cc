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