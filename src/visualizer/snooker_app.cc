/**
 * Created by Rishi Patel on 11/14/2020.
 */

#include "visualizer/snooker_app.h"
#include "core/ball.h"
#include "core/table.h"

namespace snooker {

namespace visualizer {

SnookerApp::SnookerApp() : table_(ci::Rectf(kHorizontalMargin, kVerticalMargin,
                                          kHorizontalMargin + kTableWidth,
                                          kVerticalMargin + kTableHeight)) {
  ci::app::setWindowSize(static_cast<int>(kWindowWidth),
                         static_cast<int>(kWindowHeight));
  table_.AddBall(
      Ball(glm::vec2(400, 200), glm::vec2(2, 3), kRed, kBallRadius, kBallMass));
}

void SnookerApp::update() {
  table_.IncrementTime();
}

void SnookerApp::draw() {
  ci::gl::clear(kBlack);
  ci::gl::color(kWhite);
  ci::gl::drawStrokedRect(table_.GetWalls());

  for (const Ball& ball : table_.GetBalls()) {
    ci::gl::color(ball.GetColor());
    ci::gl::drawSolidCircle(ball.GetPosition(), ball.GetRadius());
  }
}

}  // namespace visualizer

}  // namespace snooker