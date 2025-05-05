#include "qcpilot/ui/entry.h"
#include <cstdio>
#include "raylib.h"
#include "qcpilot/ui/platform.h"

namespace qcpilot {
namespace ui {
Entry::Entry(int width, int height) {
    InitWindow(width, height, "raylib [core] example - basic window");
    SetTargetFPS(60);    // Set our game to run at 60 frames-per-second
}


void Entry::start() {
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BROWN);


        // if (GuiButton((Rectangle) {200, 300, 200, 80}, "Button 2")) {
        //     const qcpilot::shott::ConsoleFrame frame = qcpilot::shott::getConsoleFrame();
        //     count = frame.engineRpm;
        // }

        const shott::ConsoleFrame frame = platform::fetchConsoleFrame();
        // const qcpilot::shott::ConsoleFrame frame = qcpilot::shott::getConsoleFrame();
        int count = frame.engineRpm;

        char buffer[256];
        int screenHeight = GetScreenHeight();
        int screenWidth = GetScreenWidth();
        std::sprintf(buffer, "Screen size: %d x %d @ %d", screenWidth, screenHeight, count);
        DrawText(buffer, 190, 200, 80, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
}

}    // namespace ui
}    // namespace qcpilot
