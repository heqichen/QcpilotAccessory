#include "qcpilot/ui/entry.h"
#include <cstdio>
#include "qcpilot/ui/layouts/fitting_layout.h"
#include "qcpilot/ui/layouts/horizontal_layout.h"
#include "qcpilot/ui/layouts/layout.h"
#include "qcpilot/ui/platform.h"
#include "raylib.h"

namespace qcpilot {
namespace ui {
Entry::Entry(int width, int height) :
    mainLayout_ {975, 450},                //
    absoluteLayout_ {0U, 0U, 600, 100},    //
    engineRpmBar_ {0U, 0U, 600, 100} {
    InitWindow(width, height, "raylib [core] example - basic window");
    SetTargetFPS(60);    // Set our game to run at 60 frames-per-second

    // engineRpmBar_.setBackgroundColor(WHITE);

    mainLayout_.setBackgroundColor(BLACK);
    mainLayout_.addChild(engineRpmBar_);
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
    mainLayout_.render(0, 0, screenWidth, screenHeight, 1.0F);

    const qcpilot::shott::ConsoleFrame frame = qcpilot::platform::fetchConsoleFrame();
    engineRpmBar_.setRpm(frame.engineRpm);

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
