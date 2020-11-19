/**
 * Created by Rishi Patel on 11/17/2020.
 */

#include "core/table.h"
#include "core/ball.h"
#include "core/table_cushion.h"
#include "cinder/gl/gl.h"
#include "catch2/catch.hpp"

#include <memory>
#include <vector>

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

TEST_CASE("Creating a Table.") {
  SECTION("Calling default constructor.") {
    Table table;

    REQUIRE(glm::vec2(100, 100) == table.GetWalls().getUpperLeft());
    REQUIRE(18 == table.GetCushions().size());
    REQUIRE(glm::vec2(100, 140) ==
            dynamic_cast<StraightCushion*>(table.GetCushions()[0].get())
                ->GetBounds().getUpperLeft());
    REQUIRE(12.5 == dynamic_cast<CurvedCushion*>(table.GetCushions()[12].get())
                        ->GetRadius());
  }

  SECTION("Calling overloaded constructor.") {
    StraightCushionPtr cushion =
        std::make_unique<StraightCushion>(ci::Rectf(100, 110, 115, 300));
    std::vector<TableCushionPtr> cushions;
    cushions.push_back(std::move(cushion));
    Table table(ci::Rectf(100, 100, 500, 500), std::move(cushions));

    REQUIRE(glm::vec2(100, 100) == table.GetWalls().getUpperLeft());
    REQUIRE(glm::vec2(500, 500) == table.GetWalls().getLowerRight());
    REQUIRE(1 == table.GetCushions().size());
  }
}

TEST_CASE("Validate adding Balls to the Table.") {
  StraightCushionPtr cushion =
      std::make_unique<StraightCushion>(ci::Rectf(100, 110, 115, 300));
  std::vector<TableCushionPtr> cushions;
  cushions.push_back(std::move(cushion));
  Table table(ci::Rectf(100, 100, 500, 500), std::move(cushions));

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

TEST_CASE("Validate incrementing the time of a Table.") {
  StraightCushionPtr cushion1 =
      std::make_unique<StraightCushion>(ci::Rectf(100, 110, 115, 300));
  StraightCushionPtr cushion2 =
      std::make_unique<StraightCushion>(ci::Rectf(130, 490, 330, 500));
  CurvedCushionPtr cushion3 =
      std::make_unique<CurvedCushion>(glm::vec2(100, 110), 15.0f);
  std::vector<TableCushionPtr> cushions;
  cushions.push_back(std::move(cushion1));
  cushions.push_back(std::move(cushion2));
  cushions.push_back(std::move(cushion3));

  Table table(ci::Rectf(100, 100, 500, 500), std::move(cushions));

  SECTION("No collisions.") {
    table.AddBall(
        Ball(glm::vec2(300, 300), glm::vec2(60, 80), ci::Color("white"), 1, 2));
    table.AddBall(
        Ball(glm::vec2(400, 300), glm::vec2(-4, 6), ci::Color("green"), 4, 5));
    table.IncrementTime();

    REQUIRE(300.571 == Approx(table.GetBalls()[0].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(300.761 == Approx(table.GetBalls()[0].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(0.571 == Approx(table.GetBalls()[0].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(0.761 == Approx(table.GetBalls()[0].GetVelocity().y).margin
                 (kMarginOfError));

    REQUIRE(399.987 == Approx(table.GetBalls()[1].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(300.0192 == Approx(table.GetBalls()[1].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(-0.013 == Approx(table.GetBalls()[1].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(0.0192 == Approx(table.GetBalls()[1].GetVelocity().y).margin
        (kMarginOfError));
  }

  SECTION("Colliding only with TableCushions.") {
    table.AddBall(Ball(glm::vec2(102, 112), glm::vec2(-130, -34),
                       ci::Color("white"), 5, 6));
    table.IncrementTime();

    REQUIRE(102.311 == Approx(table.GetBalls()[0].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(113.188 == Approx(table.GetBalls()[0].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(0.311 == Approx(table.GetBalls()[0].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(1.188 == Approx(table.GetBalls()[0].GetVelocity().y).margin
        (kMarginOfError));
  }

  SECTION("Colliding only with Balls.") {
    table.AddBall(Ball(glm::vec2(308, 300), glm::vec2(-130, 34),
                       ci::Color("white"), 5, 6));
    table.AddBall(
        Ball(glm::vec2(300, 300), glm::vec2(66, 66), ci::Color("black"), 4, 5));
    table.IncrementTime();

    REQUIRE(308.442 == Approx(table.GetBalls()[0].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(300.312 == Approx(table.GetBalls()[0].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(0.442 == Approx(table.GetBalls()[0].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(0.312 == Approx(table.GetBalls()[0].GetVelocity().y).margin
        (kMarginOfError));

    REQUIRE(298.567 == Approx(table.GetBalls()[1].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(300.640 == Approx(table.GetBalls()[1].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(-1.433 == Approx(table.GetBalls()[1].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(0.640 == Approx(table.GetBalls()[1].GetVelocity().y).margin
        (kMarginOfError));
  }

  SECTION("Multiple types of collisions.") {
    table.AddBall(Ball(glm::vec2(308, 300), glm::vec2(-130, 34),
                       ci::Color("white"), 5, 6));
    table.AddBall(
        Ball(glm::vec2(300, 300), glm::vec2(66, 66), ci::Color("black"), 4, 5));
    table.AddBall(
        Ball(glm::vec2(200, 489), glm::vec2(-4, 6), ci::Color("green"), 4, 5));
    table.IncrementTime();

    REQUIRE(308.442 == Approx(table.GetBalls()[0].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(300.312 == Approx(table.GetBalls()[0].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(0.442 == Approx(table.GetBalls()[0].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(0.312 == Approx(table.GetBalls()[0].GetVelocity().y).margin
        (kMarginOfError));

    REQUIRE(298.567 == Approx(table.GetBalls()[1].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(300.640 == Approx(table.GetBalls()[1].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(-1.433 == Approx(table.GetBalls()[1].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(0.640 == Approx(table.GetBalls()[1].GetVelocity().y).margin
        (kMarginOfError));

    REQUIRE(199.987 == Approx(table.GetBalls()[2].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(488.981 == Approx(table.GetBalls()[2].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(-0.0119 == Approx(table.GetBalls()[2].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(-0.0169 == Approx(table.GetBalls()[2].GetVelocity().y).margin
        (kMarginOfError));
  }
}