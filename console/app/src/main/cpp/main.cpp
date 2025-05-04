#define RAYGUI_NO_ICONS

#include "raymob.h" // This header can replace 'raylib.h' and includes additional functions related to Android.
#include <cstdio>
#include <jni.h>
#include <qcpilot/helper.h>

#define RAYGUI_IMPLEMENTATION

#include "raygui.h"

static int count = 0;
// char * recv = nullptr;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(0, 0, "raylib [core] example - basic window");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BROWN);


        if (GuiButton((Rectangle) {200, 300, 200, 80}, "Button 2")) {
            const qcpilot::shott::ConsoleFrame frame = qcpilot::shott::getConsoleFrame();
            count = frame.engineRpm;
        }
        const qcpilot::shott::ConsoleFrame frame = qcpilot::shott::getConsoleFrame();
        count = frame.engineRpm;

        char buffer[256];
        int screenHeight = GetScreenHeight();
        int screenWidth = GetScreenWidth();
        std::sprintf(buffer, "Screen size: %d x %d @ %d", screenWidth, screenHeight, count);
        DrawText(buffer, 190, 200, 80, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}