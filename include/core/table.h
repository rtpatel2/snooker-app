/**
 * Created by Rishi Patel on 11/15/2020.
 */

#pragma once

#include "cinder/gl/gl.h"

namespace snooker {

/** Maintains functionality of a snooker table. */
class Table {
 public:
  /**
   * Creates a new Table with the specified rectangular walls.
   *
   * @param walls Cinder rectangle specifying the walls of the Table.
   */
  Table(const ci::Rectf& walls);

 private:
  ci::Rectf walls_;
};

}  // namespace snooker