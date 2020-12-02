/**
 * Created by Rishi Patel on 12/1/2020.
 */

#include "core/game_engine.h"
#include "core/table.h"
#include "catch2/catch.hpp"

using snooker::GameEngine;
using snooker::Table;

/**
 * Testing strategy: test each function in the GameEngine class, including all
 * relevant edge cases.
 */

TEST_CASE("Validate creating a GameEngine") {
  // Sanity test -- nothing to check via REQUIREs.
  SECTION("Calling the constructor.") {
    Table table;
    GameEngine engine(&table);
  }
}