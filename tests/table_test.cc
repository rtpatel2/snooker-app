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
    REQUIRE(glm::vec2(979.75, 140) ==
            dynamic_cast<StraightCushion*>(table.GetCushions()[1].get())
                ->GetBounds().getUpperLeft());
    REQUIRE(glm::vec2(952.25, 100) ==
            dynamic_cast<StraightCushion*>(table.GetCushions()[3].get())
                ->GetBounds().getUpperRight());
    REQUIRE(glm::vec2(952.25, 532) ==
            dynamic_cast<StraightCushion*>(table.GetCushions()[5].get())
                ->GetBounds().getUpperRight());
    REQUIRE(12.5 == dynamic_cast<CurvedCushion*>(table.GetCushions()[12].get())
                        ->GetRadius());
    REQUIRE(782.313 ==
            Approx(table.GetBalls()[0].GetPosition().x).margin(kMarginOfError));
    REQUIRE(322.25 ==
            Approx(table.GetBalls()[0].GetPosition().y).margin(kMarginOfError));
    REQUIRE(808.563 ==
            Approx(table.GetBalls()[4].GetPosition().x).margin(kMarginOfError));
    REQUIRE(322.25 ==
            Approx(table.GetBalls()[4].GetPosition().y).margin(kMarginOfError));
    REQUIRE(821.688 ==
            Approx(table.GetBalls()[7].GetPosition().x).margin(kMarginOfError));
    REQUIRE(315.688 ==
            Approx(table.GetBalls()[7].GetPosition().y).margin(kMarginOfError));
    REQUIRE(glm::vec2(248.75,  358.5) == table.GetBalls().back().GetPosition());
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
    table.AddBall(Ball(glm::vec2(300, 300), glm::vec2(60, 80),
                       ci::Color("blue"), 1, 2, 1));
    REQUIRE(1 == table.GetBalls().size());
    REQUIRE(glm::vec2(300, 300) == table.GetBalls()[0].GetPosition());
  }

  SECTION("Adding multiple Balls to a Table.") {
    table.AddBall(Ball(glm::vec2(300, 300), glm::vec2(60, 80),
                       ci::Color("blue"), 1, 2, 5));
    table.AddBall(Ball(glm::vec2(400, 300), glm::vec2(-4, 6),
                       ci::Color("green"), 4, 5, 2));
    REQUIRE(2 == table.GetBalls().size());
    REQUIRE(glm::vec2(-0.04, 0.06) == table.GetBalls()[0].GetVelocity());
    REQUIRE(glm::vec2(300, 300) == table.GetBalls()[1].GetPosition());
  }

  SECTION("Attempting to add Balls outside of the walls of a Table.") {
    table.AddBall(Ball(glm::vec2(300, 300), glm::vec2(60, 80),
                       ci::Color("blue"), 1, 2, 2));
    table.AddBall(Ball(glm::vec2(40, 300), glm::vec2(-4, 6), ci::Color("green"),
                       4, 5, 3));
    REQUIRE(1 == table.GetBalls().size());
    REQUIRE(glm::vec2(300, 300) == table.GetBalls()[0].GetPosition());
  }
}

TEST_CASE("Validate simulating a time step for a Table.") {
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
    table.AddBall(Ball(glm::vec2(300, 300), glm::vec2(60, 80),
                       ci::Color("white"), 1, 2, 4));
    table.AddBall(Ball(glm::vec2(400, 300), glm::vec2(-4, 6),
                       ci::Color("green"), 4, 5, 5));
    table.SimulateTimeStep();

    REQUIRE(300.576 == Approx(table.GetBalls()[0].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(300.769 == Approx(table.GetBalls()[0].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(0.576 == Approx(table.GetBalls()[0].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(0.769 == Approx(table.GetBalls()[0].GetVelocity().y).margin
                 (kMarginOfError));

    REQUIRE(399.982 == Approx(table.GetBalls()[1].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(300.027 == Approx(table.GetBalls()[1].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(-0.0183 == Approx(table.GetBalls()[1].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(0.02738 == Approx(table.GetBalls()[1].GetVelocity().y).margin
        (kMarginOfError));
  }

  SECTION("Colliding only with TableCushions.") {
    table.AddBall(Ball(glm::vec2(102, 112), glm::vec2(-130, -34),
                       ci::Color("white"), 5, 6, 9));
    table.SimulateTimeStep();

    REQUIRE(102.313 == Approx(table.GetBalls()[0].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(113.197 == Approx(table.GetBalls()[0].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(0.313 == Approx(table.GetBalls()[0].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(1.197 == Approx(table.GetBalls()[0].GetVelocity().y).margin
        (kMarginOfError));
  }

  SECTION("Colliding only with Balls.") {
    table.AddBall(Ball(glm::vec2(308, 300), glm::vec2(-130, 34),
                       ci::Color("white"), 5, 6, 12));
    table.AddBall(Ball(glm::vec2(300, 300), glm::vec2(66, 66),
                       ci::Color("black"), 4, 5, 15));
    table.SimulateTimeStep();

    REQUIRE(308.450 == Approx(table.GetBalls()[0].GetPosition().x)
                           .margin(kMarginOfError));
    REQUIRE(300.317 == Approx(table.GetBalls()[0].GetPosition().y)
                           .margin(kMarginOfError));
    REQUIRE(0.450 == Approx(table.GetBalls()[0].GetVelocity().x)
                         .margin(kMarginOfError));
    REQUIRE(0.317 == Approx(table.GetBalls()[0].GetVelocity().y)
                         .margin(kMarginOfError));

    REQUIRE(298.558 == Approx(table.GetBalls()[1].GetPosition().x)
                           .margin(kMarginOfError));
    REQUIRE(300.644 == Approx(table.GetBalls()[1].GetPosition().y)
                           .margin(kMarginOfError));
    REQUIRE(-1.442 == Approx(table.GetBalls()[1].GetVelocity().x)
                          .margin(kMarginOfError));
    REQUIRE(0.644 == Approx(table.GetBalls()[1].GetVelocity().y)
                         .margin(kMarginOfError));
  }

  SECTION("Multiple types of collisions.") {
    table.AddBall(Ball(glm::vec2(308, 300), glm::vec2(-130, 34),
                       ci::Color("white"), 5, 6, 15));
    table.AddBall(Ball(glm::vec2(300, 300), glm::vec2(66, 66),
                       ci::Color("black"), 4, 5, 15));
    table.AddBall(Ball(glm::vec2(200, 489), glm::vec2(-4, 6),
                       ci::Color("green"), 4, 5, 15));
    table.SimulateTimeStep();

    REQUIRE(308.450 == Approx(table.GetBalls()[0].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(300.317 == Approx(table.GetBalls()[0].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(0.450 == Approx(table.GetBalls()[0].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(0.317 == Approx(table.GetBalls()[0].GetVelocity().y).margin
        (kMarginOfError));

    REQUIRE(298.558 == Approx(table.GetBalls()[1].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(300.644 == Approx(table.GetBalls()[1].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(-1.442 == Approx(table.GetBalls()[1].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(0.644 == Approx(table.GetBalls()[1].GetVelocity().y).margin
        (kMarginOfError));

    REQUIRE(199.983 == Approx(table.GetBalls()[2].GetPosition().x).margin
        (kMarginOfError));
    REQUIRE(488.975 == Approx(table.GetBalls()[2].GetPosition().y).margin
        (kMarginOfError));
    REQUIRE(-0.0175 == Approx(table.GetBalls()[2].GetVelocity().x).margin
        (kMarginOfError));
    REQUIRE(-0.0249 == Approx(table.GetBalls()[2].GetVelocity().y).margin
        (kMarginOfError));
  }
}

TEST_CASE("Validate checking if a Table is steady.") {
  Table table;

  SECTION("Correctly identifying a steady Table as steady.") {
    table.SetCueBallVelocity(glm::vec2(0, 0));
    REQUIRE(table.IsSteady());
  }

  SECTION("Correctly identifying a Table with moving Balls as not steady.") {
    table.SetCueBallVelocity(glm::vec2(1, 4));
    REQUIRE_FALSE(table.IsSteady());
  }
}

TEST_CASE("Validate resetting first contacted.") {
  Table table;

  SECTION("Resetting first contacted for a Table with no contact.") {
    table.ResetFirstContacted();
    for (const Ball& ball : table.GetBalls()) {
      REQUIRE(Ball::kNoContactColor == ball.GetFirstContacted());
    }
  }

  SECTION("Resetting first contacted for a Table after a stroke.") {
    table.SetCueBallVelocity(glm::vec2(17, -3));
    while (!table.IsSteady()) {
      table.SimulateTimeStep();
    }
    table.ResetFirstContacted();
    for (const Ball& ball : table.GetBalls()) {
      REQUIRE(Ball::kNoContactColor == ball.GetFirstContacted());
    }
  }
}

TEST_CASE("Validate removing a Ball from the Table.") {
  Table table;

  SECTION("Removing a red Ball.") {
    Ball ball(glm::vec2(113, 113), glm::vec2(0, 0), ci::Color("red"), 5, 5, 1);
    table.AddBall(ball);
    REQUIRE(23 == table.GetBalls().size());
    REQUIRE(16 == table.GetRedBallCount());
    Ball copy_ball(glm::vec2(113, 113), glm::vec2(0, 0), ci::Color("red"), 5,
                   5, 1);
    table.RemoveBallFromTable(copy_ball);
    REQUIRE(22 == table.GetBalls().size());
    REQUIRE(15 == table.GetRedBallCount());
  }

  SECTION("Removing a red and color Ball.") {
    table.RemoveBallFromTable(table.GetBalls().front());
    table.RemoveBallFromTable(table.GetBalls().back());
    REQUIRE(20 == table.GetBalls().size());
    REQUIRE(14 == table.GetRedBallCount());
  }
}

TEST_CASE("Validate finding the lowest point value color.") {
  Table table;

  SECTION("Finding lowest point value color without removing any Balls.") {
    REQUIRE(Ball::kRed == table.FindLeastPointValueColor());
  }

  SECTION("Finding lowest point value color after reds are removed.") {
    for (size_t ball = 0; ball < 15; ++ball) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    REQUIRE(Ball::kYellow == table.FindLeastPointValueColor());
  }

  SECTION("Finding lowest point value color with only black remaining.") {
    for (size_t ball = 0; ball < 20; ++ball) {
      table.RemoveBallFromTable(table.GetBalls().front());
    }
    REQUIRE(Ball::kBlack == table.FindLeastPointValueColor());
  }
}