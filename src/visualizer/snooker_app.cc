/**
 * Created by Rishi Patel on 11/14/2020.
 */

#include "visualizer/snooker_app.h"

namespace snooker {

namespace visualizer {

SnookerApp::SnookerApp() : table_(ci::Rectf(kHorizontalMargin, kVerticalMargin,
                                          kHorizontalMargin + kTableWidth,
                                          kVerticalMargin + kTableHeight)) {
  ci::app::setWindowSize(static_cast<int>(kWindowWidth),
                         static_cast<int>(kWindowHeight));
}


}  // namespace visualizer

}  // namespace snooker