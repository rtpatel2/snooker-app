/**
 * Created by Rishi Patel on 11/14/2020.
 */

#include "visualizer/snooker_app.h"
#include "core/ball.h"
#include "core/table.h"
#include "core/cue.h"
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
  //TODO: Move this into GameEngine too?
  table_.IncrementTime();
  engine_.AssessTable();
}

void SnookerApp::draw() {
  ci::gl::clear(kBlack);
  ci::gl::color(kTableColor);
  ci::gl::drawSolidRect(table_.GetWalls());
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

  ci::gl::color(kRailColor);
  ci::Rectf rails(
      Table::kHorizontalMargin - Table::kCushionWidth / 2,
      Table::kVerticalMargin - Table::kCushionWidth / 2,
      Table::kHorizontalMargin + Table::kTableWidth + Table::kCushionWidth / 2,
      Table::kVerticalMargin + Table::kTableHeight + Table::kCushionWidth / 2);
  ci::gl::drawStrokedRect(rails, Table::kCushionWidth);

  for (const Ball& ball : table_.GetBalls()) {
    ci::gl::color(ball.GetColor());
    ci::gl::drawSolidCircle(ball.GetPosition(), ball.GetRadius());
  }

  for (const Pocket& pocket : table_.GetPockets()) {
    ci::gl::color(pocket.GetColor());
    ci::gl::drawSolidCircle(pocket.GetPosition(), pocket.GetRadius());
  }

  if (table_.IsSteady()) {
    ci::gl::ScopedModelMatrix scoped_matrix;
    ci::gl::translate(table_.GetBalls().back().GetPosition());

    glm::vec2 mouse_position = getMousePos() - getWindowPos();
    glm::vec2 cue_vector =
        table_.GetBalls().back().GetPosition() - mouse_position;
    float cue_angle = glm::atan(cue_vector.y / cue_vector.x);
    cue_angle += (cue_vector.x < 0) ? static_cast<float>(M_PI) : 0;
    ci::gl::rotate(cue_angle);
    ci::gl::color(ci::Color("brown"));

    ci::gl::drawSolidRect(ci::Rectf(
        -Cue::kCueLength - table_.GetCuePullBack(), -Cue::kCueWidth,
        -Table::kBallRadius - table_.GetCuePullBack(), Cue::kCueWidth));
  }
}

void SnookerApp::mouseUp(ci::app::MouseEvent event) {
  table_.HandleStrokeEnd(static_cast<glm::vec2>(event.getPos()));
}

void SnookerApp::mouseDown(ci::app::MouseEvent event) {
  table_.HandleStrokeStart(static_cast<glm::vec2>(event.getPos()));
}

void SnookerApp::mouseDrag(ci::app::MouseEvent event) {
  table_.HandleCuePullBack(static_cast<glm::vec2>(event.getPos()));
}

}  // namespace visualizer

}  // namespace snooker