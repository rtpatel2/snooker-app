/**
 * Created by Rishi Patel on 11/15/2020.
 */

#include "core/table.h"
#include "cinder/gl/gl.h"

namespace snooker {

Table::Table(const ci::Rectf& walls) : walls_(walls) {}

void Table::AddBall(const Ball& ball) {
  if (walls_.contains(ball.GetPosition())) {
    balls_.push_back(ball);
  }
}

}  // namespace snooker