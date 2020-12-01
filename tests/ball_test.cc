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
              12.3f, 4.3f, 5);
    REQUIRE(glm::vec2(300, 400) == ball.GetPosition());
    REQUIRE(glm::vec2(-0.012, 0.034) == ball.GetVelocity());
    REQUIRE(ci::Color("red") == ball.GetColor());
    REQUIRE(12.3f == ball.GetRadius());
    REQUIRE(4.3f == ball.GetMass());
    REQUIRE(5 == ball.GetPointValue());
  }
}

TEST_CASE("Validate updating a Ball's position.") {
  SECTION("Ball with non-zero velocity components.") {
    Ball ball(glm::vec2(100, 100), glm::vec2(40, 30), ci::Color("white"), 1, 1,
              3);
    ball.UpdatePosition();
    REQUIRE(0.3686 == Approx(ball.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0.2765 == Approx(ball.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(100.3686 == Approx(ball.GetPosition().x).margin(kMarginOfError));
    REQUIRE(100.2765 == Approx(ball.GetPosition().y).margin(kMarginOfError));
  }

  SECTION("Ball with one non-zero velocity component.") {
    Ball ball(glm::vec2(100, 100), glm::vec2(0, -300), ci::Color("white"), 1, 1,
              1);
    ball.UpdatePosition();
    REQUIRE(0 == Approx(ball.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(-2.961 == Approx(ball.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(100 == Approx(ball.GetPosition().x).margin(kMarginOfError));
    REQUIRE(97.0392 == Approx(ball.GetPosition().y).margin(kMarginOfError));
  }

  SECTION("Ball with zero speed.") {
    Ball ball(glm::vec2(345, 677), glm::vec2(0, 0), ci::Color("white"), 1, 1,
              2);
    ball.UpdatePosition();
    REQUIRE(0 == Approx(ball.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(345 == Approx(ball.GetPosition().x).margin(kMarginOfError));
    REQUIRE(677 == Approx(ball.GetPosition().y).margin(kMarginOfError));
  }

  SECTION("Ball coming to a stop due to friction.") {
    Ball ball(glm::vec2(300, 400), glm::vec2(-1.2, 3.4), ci::Color("red"),
              12.3f, 4.3f, 6);
    ball.UpdatePosition();
    REQUIRE(0 == Approx(ball.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(300 == Approx(ball.GetPosition().x).margin(kMarginOfError));
    REQUIRE(400 == Approx(ball.GetPosition().y).margin(kMarginOfError));
  }
}

TEST_CASE("Validate computing velocity after collision with another Ball.") {
  SECTION("Colliding a ball head-on with another ball.") {
    Ball ball1(glm::vec2(565.3, 927.5), glm::vec2(-0.6, 0), ci::Color("white"),
               5, 5, 7);
    Ball ball2(glm::vec2(564.8, 927.5), glm::vec2(0.6, 0), ci::Color("white"),
               5, 5, 8);

    glm::vec2 ball1_new_velocity = ball1.ComputeVelocityAfterCollision(ball2);
    glm::vec2 ball2_new_velocity = ball2.ComputeVelocityAfterCollision(ball1);
    ball1.SetVelocity(ball1_new_velocity);
    ball2.SetVelocity(ball2_new_velocity);
    REQUIRE(0.006 == Approx(ball1.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball1.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(-0.006 == Approx(ball2.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball2.GetVelocity().y).margin(kMarginOfError));
  }

  SECTION("Colliding a ball off-center with another ball.") {
    Ball ball1(glm::vec2(320.0, 620.0), glm::vec2(0.1, 0.0), ci::Color("white"),
               2.34f, 1, 9);
    Ball ball2(glm::vec2(321.4, 621.4), glm::vec2(-0.1, 0.0),
               ci::Color("white"), 3.4f, 1, 10);

    glm::vec2 ball1_new_velocity = ball1.ComputeVelocityAfterCollision(ball2);
    glm::vec2 ball2_new_velocity = ball2.ComputeVelocityAfterCollision(ball1);
    ball1.SetVelocity(ball1_new_velocity);
    ball2.SetVelocity(ball2_new_velocity);
    REQUIRE(0 == Approx(ball1.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(-0.001 == Approx(ball1.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball2.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0.001 == Approx(ball2.GetVelocity().y).margin(kMarginOfError));

    ball1.UpdatePosition();
    ball2.UpdatePosition();
    REQUIRE(320 == Approx(ball1.GetPosition().x).margin(kMarginOfError));
    REQUIRE(619.999 == Approx(ball1.GetPosition().y).margin(kMarginOfError));
    REQUIRE(321.4 == Approx(ball2.GetPosition().x).margin(kMarginOfError));
    REQUIRE(621.401 == Approx(ball2.GetPosition().y).margin(kMarginOfError));
  }

  SECTION("Colliding balls with different masses.") {
    Ball ball1(glm::vec2(450.0, 450.0), glm::vec2(1.2, 0), ci::Color("white"),
               2.0f, 3.4f, 11);
    Ball ball2(glm::vec2(453.0, 450.0), glm::vec2(-0.3, 0), ci::Color("red"),
               1.4f, 5.3f, 1);

    glm::vec2 ball1_new_velocity = ball1.ComputeVelocityAfterCollision(ball2);
    glm::vec2 ball2_new_velocity = ball2.ComputeVelocityAfterCollision(ball1);
    ball1.SetVelocity(ball1_new_velocity);
    ball2.SetVelocity(ball2_new_velocity);
    REQUIRE(-0.006276 == Approx(ball1.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball1.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(0.008724 == Approx(ball2.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball2.GetVelocity().y).margin(kMarginOfError));
  }

  SECTION("No collision between balls overlapping but moving away.") {
    Ball ball1(glm::vec2(450.0, 450.0), glm::vec2(-1.2, 0), ci::Color("white"),
               2.0f, 3.4f, 2);
    Ball ball2(glm::vec2(453.0, 450.0), glm::vec2(0.3, 0), ci::Color("red"),
               1.4f, 5.3f, 4);

    glm::vec2 ball1_new_velocity = ball1.ComputeVelocityAfterCollision(ball2);
    glm::vec2 ball2_new_velocity = ball2.ComputeVelocityAfterCollision(ball1);
    ball1.SetVelocity(ball1_new_velocity);
    ball2.SetVelocity(ball2_new_velocity);
    REQUIRE(-0.012 == Approx(ball1.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball1.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(0.003 == Approx(ball2.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball2.GetVelocity().y).margin(kMarginOfError));
  }

  SECTION("No collision between balls touching but moving away.") {
    Ball ball1(glm::vec2(320.0, 620.0), glm::vec2(-0.1, 0.0),
               ci::Color("white"), 3.45f, 5, 6);
    Ball ball2(glm::vec2(321.4, 621.4), glm::vec2(0.1, 0.0), ci::Color("white"),
               3, 4, 8);

    glm::vec2 ball1_new_velocity = ball1.ComputeVelocityAfterCollision(ball2);
    glm::vec2 ball2_new_velocity = ball2.ComputeVelocityAfterCollision(ball1);
    ball1.SetVelocity(ball1_new_velocity);
    ball2.SetVelocity(ball2_new_velocity);
    REQUIRE(-0.001 == Approx(ball1.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball1.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(0.001 == Approx(ball2.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball2.GetVelocity().y).margin(kMarginOfError));
  }

  SECTION("No collision between balls not touching but moving closer.") {
    Ball ball1(glm::vec2(320.0, 620.0), glm::vec2(0.1, 0.0), ci::Color("white"),
               1, 1, 10);
    Ball ball2(glm::vec2(351.4, 621.4), glm::vec2(-0.1, 0.0),
               ci::Color("white"), 1, 1, 12);

    glm::vec2 ball1_new_velocity = ball1.ComputeVelocityAfterCollision(ball2);
    glm::vec2 ball2_new_velocity = ball2.ComputeVelocityAfterCollision(ball1);
    ball1.SetVelocity(ball1_new_velocity);
    ball2.SetVelocity(ball2_new_velocity);
    REQUIRE(0.001 == Approx(ball1.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball1.GetVelocity().y).margin(kMarginOfError));
    REQUIRE(-0.001 == Approx(ball2.GetVelocity().x).margin(kMarginOfError));
    REQUIRE(0 == Approx(ball2.GetVelocity().y).margin(kMarginOfError));
  }
}

TEST_CASE("Validate < operator overloading.") {
  Ball ball1(glm::vec2(320.0, 620.0), glm::vec2(0.1, 0.0), ci::Color("white"),
             1, 1, 10);
  Ball ball2(glm::vec2(351.4, 621.4), glm::vec2(-0.1, 0.0),
             ci::Color("white"), 1, 1, 12);
  Ball ball3(glm::vec2(351.4, 621.4), glm::vec2(-0.1, 0.0),
             ci::Color("white"), 1, 1, 10);

  SECTION("Calling Ball has lower point value than the object Ball.") {
    REQUIRE(ball1 < ball2);
  }

  SECTION("Calling Ball has greater point value than the object Ball.") {
    REQUIRE_FALSE(ball2 < ball1);
  }

  SECTION("Calling Ball has equal point value than the object Ball.") {
    REQUIRE_FALSE(ball2 < ball3);
  }
}

TEST_CASE("Validate == operator overloading.") {
  Ball ball1(glm::vec2(500.3, 600.2), glm::vec2(-1, 2), ci::Color("white"),
             1, 2, 3);
  Ball ball2(glm::vec2(500.299, 600.199), glm::vec2(-5, -7),
             ci::Color("green"), 4, 5, 6);
  Ball ball3(glm::vec2(351.4, 621.4), glm::vec2(3.14, 2.71),
             ci::Color("blue"), 7, 8, 9);

  SECTION("Classify Balls with identical initial positions as equal.") {
    REQUIRE(ball1 == ball2);
  }

  SECTION("Classify Balls with different initial positions as nonequal.") {
    REQUIRE_FALSE(ball1 == ball3);
    REQUIRE_FALSE(ball2 == ball3);
  }
}