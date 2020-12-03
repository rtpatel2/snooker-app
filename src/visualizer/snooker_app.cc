/**
 * Created by Rishi Patel on 11/14/2020.
 */

#include "visualizer/snooker_app.h"
#include "core/ball.h"
#include "core/table.h"
#include "core/pocket.h"
#include "core/game_engine.h"
#include "cinder/gl/gl.h"

namespace snooker {

namespace visualizer {

SnookerApp::SnookerApp() : engine_(&table_) {
  ci::app::setWindowSize(static_cast<int>(kWindowWidth),
                         static_cast<int>(kWindowHeight));
}

void SnookerApp::update() {
  table_.IncrementTime();
  engine_.PocketBalls();
}

void SnookerApp::draw() {
  ci::gl::clear(kBlack);
  DrawTableFelt();
  DrawCushions();
  DrawRails();
  DrawPockets();
  DrawCue();
  DrawBalls();
  DrawCurrentPlayer();
}

void SnookerApp::mouseUp(ci::app::MouseEvent event) {
  engine_.HandleStrokeEnd(static_cast<glm::vec2>(event.getPos()));
}

void SnookerApp::mouseDown(ci::app::MouseEvent event) {
  engine_.HandleStrokeStart(static_cast<glm::vec2>(event.getPos()));
}

void SnookerApp::mouseDrag(ci::app::MouseEvent event) {
  engine_.HandleCuePullBack(static_cast<glm::vec2>(event.getPos()));
}

void SnookerApp::DrawTableFelt() const {
  ci::gl::color(kTableColor);
  ci::gl::drawSolidRect(table_.GetWalls());
}

void SnookerApp::DrawCushions() const {
  ci::gl::color(kCushionColor);
  for (const std::unique_ptr<TableCushion>& cushion : table_.GetCushions()) {
    if (dynamic_cast<StraightCushion*>(cushion.get())) {
      ci::gl::drawSolidRect(
          dynamic_cast<StraightCushion*>(cushion.get())->GetBounds());
    } else if (dynamic_cast<CurvedCushion*>(cushion.get())) {
      CurvedCushion* curved_cushion =
          dynamic_cast<CurvedCushion*>(cushion.get());
      ci::gl::drawSolidCircle(curved_cushion->GetPosition(),
                              curved_cushion->GetRadius());
    }
  }
}

void SnookerApp::DrawRails() const {
  ci::gl::color(kRailColor);
  ci::Rectf rails(
      Table::kHorizontalMargin - Table::kCushionWidth / 2,
      Table::kVerticalMargin - Table::kCushionWidth / 2,
      Table::kHorizontalMargin + Table::kTableWidth + Table::kCushionWidth / 2,
      Table::kVerticalMargin + Table::kTableHeight + Table::kCushionWidth / 2);
  ci::gl::drawStrokedRect(rails, Table::kCushionWidth);
}

void SnookerApp::DrawPockets() const {
  for (const Pocket& pocket : table_.GetPockets()) {
    ci::gl::color(pocket.GetColor());
    ci::gl::drawSolidCircle(pocket.GetPosition(), pocket.GetRadius());
  }
}

void SnookerApp::DrawCue() const {
  if (table_.IsSteady()) {
    ci::gl::ScopedModelMatrix scoped_matrix;
    ci::gl::translate(table_.GetBalls().back().GetPosition());

    glm::vec2 mouse_position = getMousePos() - getWindowPos();
    ci::gl::rotate(engine_.ComputeCueAngle(mouse_position));
    ci::gl::color(ci::Color("brown"));

    ci::gl::drawSolidRect(engine_.ComputeCueDimensions());
  }
}

void SnookerApp::DrawBalls() const {
  for (const Ball& ball : table_.GetBalls()) {
    ci::gl::color(ball.GetColor());
    ci::gl::drawSolidCircle(ball.GetPosition(), ball.GetRadius());
  }
}

void SnookerApp::DrawCurrentPlayer() const {
  if (engine_.IsPlayer1Turn()) {
    ci::gl::drawStringCentered("Player 1", glm::vec2(150, 300), kWhite);
  } else {
    ci::gl::drawStringCentered("Player 2", glm::vec2(150, 300), kWhite);
  }
}

}  // namespace visualizer

}  // namespace snooker