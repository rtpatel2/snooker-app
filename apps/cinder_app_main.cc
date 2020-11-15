#include <visualizer/snooker_app.h>

using snooker::visualizer::SnookerApp;

void prepareSettings(SnookerApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(SnookerApp, ci::app::RendererGl, prepareSettings);