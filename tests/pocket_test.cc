/**
 * Created by Rishi Patel on 12/1/2020.
 */

#include "core/pocket.h"
#include "cinder/gl/gl.h"
#include "catch2/catch.hpp"

using snooker::Pocket;

/**
 * Testing strategy: test each function in the Pocket class, including all
 * relevant edge cases.
 */

TEST_CASE("Creating a Pocket.") {
  SECTION("Calling the constructor.") {
    Pocket pocket(glm::vec2(500, 500), 15, ci::Color("black"));
    REQUIRE(glm::vec2(500, 500) == pocket.GetPosition());
    REQUIRE(15 == pocket.GetRadius());
    REQUIRE(ci::Color("black") == pocket.GetColor());
  }
}