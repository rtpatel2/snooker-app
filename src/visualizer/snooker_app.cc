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
  if (!engine_.IsGameOver()) {
    table_.SimulateTimeStep();
    engine_.PocketBalls();
    engine_.PerformCPUStroke();
  }
}

void SnookerApp::draw() {
  ci::gl::clear(kBlack);
  DrawTableFelt();
  DrawCushions();
  DrawRails();
  DrawPockets();
  DrawBalls();
  DrawCue();
  DrawCurrentPlayer();
  DrawPlayerScores();

  DrawEndGameScreen();
}

void SnookerApp::mouseUp(ci::app::MouseEvent event) {
  if (!engine_.GetCurrentPlayer()->IsCPUControlled()) {
    engine_.HandleStrokeEnd(static_cast<glm::vec2>(event.getPos()));
  }
}

void SnookerApp::mouseDown(ci::app::MouseEvent event) {
  if (!engine_.GetCurrentPlayer()->IsCPUControlled()) {
    engine_.HandleStrokeStart(static_cast<glm::vec2>(event.getPos()));
  }
}

void SnookerApp::mouseDrag(ci::app::MouseEvent event) {
  if (!engine_.GetCurrentPlayer()->IsCPUControlled()) {
    engine_.HandleCuePullBack(static_cast<glm::vec2>(event.getPos()));
  }
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

    glm::vec2 mouse_position;
    if (!engine_.GetCurrentPlayer()->IsCPUControlled()) {
      mouse_position = getMousePos() - getWindowPos();
    } else {
      mouse_position = engine_.GetStrokeCurrentPosition();
    }

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
  glm::vec2 position(Table::kHorizontalMargin + Table::kTableWidth / 2,
                     Table::kVerticalMargin / 4);
  if (engine_.IsPlayer1Turn()) {
    ci::gl::drawStringCentered("PLAYER 1 TURN", position, kWhite, kDefaultFont);
  } else {
    ci::gl::drawStringCentered("PLAYER 2 TURN", position, kWhite, kDefaultFont);
  }
}

void SnookerApp::DrawPlayerScores() const {
  ci::gl::drawStringCentered(
      "PLAYER 1 SCORE: " + std::to_string(engine_.GetPlayer1().GetScore()),
      glm::vec2(Table::kHorizontalMargin + Table::kTableWidth / 4,
                Table::kVerticalMargin / 2),
      kWhite, kDefaultFont);

  ci::gl::drawStringCentered(
      "PLAYER 2 SCORE: " + std::to_string(engine_.GetPlayer2().GetScore()),
      glm::vec2(Table::kHorizontalMargin + Table::kTableWidth * 3 / 4,
                Table::kVerticalMargin / 2),
      kWhite, kDefaultFont);
}

void SnookerApp::DrawEndGameScreen() const {
  if (engine_.IsGameOver()) {
    ci::gl::color(kGray);
    ci::Rectf window(
        Table::kHorizontalMargin + Table::kTableWidth / 2 - kEndScreenWidth / 2,
        Table::kVerticalMargin + Table::kTableHeight / 2 - kEndScreenHeight / 2,
        Table::kHorizontalMargin + Table::kTableWidth / 2 + kEndScreenWidth / 2,
        Table::kVerticalMargin + Table::kTableHeight / 2 +
            kEndScreenHeight / 2);
    ci::gl::drawSolidRect(window);

    glm::vec2 game_status_position((window.x1 + window.x2) / 2,
                                           window.y1 + kEndScreenHeight / 4);
    if (engine_.GetPlayer1().GetScore() == engine_.GetPlayer2().GetScore()) {
      ci::gl::drawStringCentered("DRAW", game_status_position, kWhite,
                                 kLargeFont);
    } else if (engine_.GetPlayer1().GetScore() >
               engine_.GetPlayer2().GetScore()) {
      ci::gl::drawStringCentered("PLAYER 1 WINS!", game_status_position, kWhite,
                                 kLargeFont);
    } else {
      ci::gl::drawStringCentered("PLAYER 2 WINS!", game_status_position, kWhite,
                                 kLargeFont);
    }

    glm::vec2 score_position((window.x1 + window.x2) / 2,
                             window.y1 + kEndScreenHeight / 2);
    ci::gl::drawStringCentered(
        std::to_string(engine_.GetPlayer1().GetScore()) + " - " +
            std::to_string(engine_.GetPlayer2().GetScore()),
        score_position, kWhite, kLargeFont);
    }
}

}  // namespace visualizer

}  // namespace snooker