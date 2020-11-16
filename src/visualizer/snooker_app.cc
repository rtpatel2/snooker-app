/**
 * Created by Rishi Patel on 11/14/2020.
 */

#include "visualizer/snooker_app.h"
#include "core/ball.h"
#include "core/table.h"

#include <vector>

namespace snooker {

namespace visualizer {

SnookerApp::SnookerApp() {
  std::vector<StraightEdge> edges{StraightEdge(ci::Rectf(
      kHorizontalMargin, kVerticalMargin, kHorizontalMargin + kTableEdgeWidth,
      kVerticalMargin + kTableHeight))};
  table_ = Table(ci::Rectf(kHorizontalMargin, kVerticalMargin,
                           kHorizontalMargin + kTableWidth,
                           kVerticalMargin + kTableHeight),
                 edges);
  ci::app::setWindowSize(static_cast<int>(kWindowWidth),
                         static_cast<int>(kWindowHeight));
  float left_wall = table_.GetWalls().x1;
  float right_wall = table_.GetWalls().x2;
  float top_wall = table_.GetWalls().y1;
  float bottom_wall = table_.GetWalls().y2;

  table_.AddBall(Ball(glm::vec2(left_wall + kBaulkLinePosition + 400,
                                top_wall + (bottom_wall - top_wall) / 2),
                      glm::vec2(-1300, 0), kWhite, kBallRadius, kBallMass));
  table_.AddBall(Ball(glm::vec2(left_wall + kBaulkLinePosition,
                                top_wall + (bottom_wall - top_wall) / 2),
                      glm::vec2(0, 0), kBrown, kBallRadius, kBallMass));
}

void SnookerApp::update() {
  table_.IncrementTime();
}

void SnookerApp::draw() {
  ci::gl::clear(kBlack);
  ci::gl::color(kTableCloth);
  ci::gl::drawSolidRect(table_.GetWalls());
  ci::gl::color(kTableEdge);
  for (const StraightEdge& component : table_.GetComponents()) {
    ci::gl::drawSolidRect(component.GetBounds());
  }

  //ci::gl::drawStrokedRect(table_.GetWalls(), kTableEdgeWidth);

  for (const Ball& ball : table_.GetBalls()) {
    ci::gl::color(ball.GetColor());
    ci::gl::drawSolidCircle(ball.GetPosition(), ball.GetRadius());
  }
}

}  // namespace visualizer

}  // namespace snooker