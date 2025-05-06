#include "qcpilot/ui/entry.h"
#include <cstdio>
#include "qcpilot/ui/layouts/fitting_layout.h"
// #include "qcpilot/ui/layouts/horizontal_layout.h"
// #include "qcpilot/ui/layouts/layout.h"
#include "qcpilot/ui/layouts/engine_rpm_bar.h"
#include "qcpilot/ui/platform.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {
Entry::Entry(int width, int height) :
    mainLayout_ {ui::CanvasSize {975, 450}},    //
                                                // absoluteLayout_ {0U, 0U, 600, 100},    //
    engineRpmBar_ {ui::CanvasArea {0U, 0U, 600U, 100U}},
    engineRpmText_ {ui::CanvasArea {600U, 0U, 200U, 100U}} {
    InitWindow(width, height, "raylib [core] example - basic window");
    SetTargetFPS(60);    // Set our game to run at 60 frames-per-second


    engineRpmText_.setBackgroundColor(RED);
    mainLayout_.setBackgroundColor(BLACK);
    mainLayout_.addChild(engineRpmBar_);
    mainLayout_.addChild(engineRpmText_);
}


void Entry::start() {
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BROWN);
        tick();

        EndDrawing();
    }
    CloseWindow();
}

void Entry::tick() {
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    mainLayout_.renderAll(
      ui::ScreenViewport {0, 0, static_cast<std::size_t>(screenWidth), static_cast<std::size_t>(screenHeight)}, 1.0F);

    const qcpilot::shott::ConsoleFrame frame = qcpilot::platform::fetchConsoleFrame();
    engineRpmBar_.setRpm(frame.engineRpm);
    engineRpmText_.setRpm(frame.engineRpm);

    // if (GuiButton((Rectangle) {200, 300, 200, 80}, "Button 2")) {
    //     const qcpilot::shott::ConsoleFrame frame = qcpilot::shott::getConsoleFrame();
    //     count = frame.engineRpm;
    // }

    // const shott::ConsoleFrame frame = platform::fetchConsoleFrame();
    // // const qcpilot::shott::ConsoleFrame frame = qcpilot::shott::getConsoleFrame();
    // int count = frame.engineRpm;

    char buffer[256];
    std::sprintf(buffer, "Screen size: %d x %d", screenWidth, screenHeight);
    DrawText(buffer, 190, 200, 80, LIGHTGRAY);
}

}    // namespace ui
}    // namespace qcpilot
