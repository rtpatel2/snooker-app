/**
 * Created by Rishi Patel on 11/28/2020.
 */

#pragma once

#include "table.h"

namespace snooker {

/** Maintains functionality of a snooker cue. */
class Cue {
 public:
  Cue();

  static constexpr float kCueLength = 100 * Table::kScalingFactor;
  static constexpr float kCueWidth = 1 * Table::kScalingFactor;
  static constexpr float kMaxPullBack = 50 * Table::kScalingFactor;
};

}  // namespace snooker