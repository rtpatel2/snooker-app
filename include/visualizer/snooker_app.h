/**
 * Created by Rishi Patel on 11/14/2020.
 */

#pragma once

#include "cinder/gl/gl.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"

namespace snooker {

namespace visualizer {

/** Allows a user to visualize a game of snooker. */
class SnookerApp : public ci::app::App {
 public:
  /** Initializes a new SnookerApp. */
  SnookerApp();

  /** Performs once per loop computations to be used in draw(). */
  void update() override;

  /** Renders the current state of the snooker visualization. */
  void draw() override;
};

}  // namespace visualizer

}  // namespace snooker