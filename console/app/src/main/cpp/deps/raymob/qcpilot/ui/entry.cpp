#include "qcpilot/ui/entry.h"
#include <cstdio>
#include "qcpilot/ui/layouts/engine_rpm_bar.h"
#include "qcpilot/ui/layouts/fitting_layout.h"
#include "qcpilot/ui/layouts/pedal.h"
#include "qcpilot/ui/platform.h"
#include "raylib.h"


namespace qcpilot {
namespace ui {
Entry::Entry(int width, int height) :
    mainLayout_ {ui::CanvasSize {975, 450}},    //
                                                // absoluteLayout_ {0U, 0U, 600, 100},    //
    engineRpmBar_ {ui::CanvasArea {0U, 0U, 600U, 100U}},
    engineRpmText_ {ui::CanvasArea {600U, 0U, 200U, 100U}},
    speedText_ {ui::CanvasArea {75U, 75U, 375U, 225U}},
    acceleration_ {ui::CanvasArea {550U, 75U, 225U, 225U}},
    brakePedal_ {"BRAKE", ui::CanvasArea {75U, 300U, 325U, 100U}, RED},
    gasPedal_ {"THROTTLE", ui::CanvasArea {450U, 300U, 325U, 100U}, LIME},
    linkState_ {ui::CanvasArea {50U, 400U, 50U, 50U}},
    textBox_ {ui::CanvasArea {120U, 400U, 400U, 50U}},
    testButton_ {ui::CanvasArea {800U, 50U, 130U, 50U}} {
    InitWindow(width, height, "raylib [core] example - basic window");
    SetTargetFPS(60);    // Set our game to run at 60 frames-per-second


    // speedText_.setBackgroundColor(RED);
    // acceleration_.setBackgroundColor(DARKBLUE);
    // brakePedal_.setBackgroundColor(VIOLET);
    // gasPedal_.setBackgroundColor(LIME);

    mainLayout_.setBackgroundColor(BLACK);
    mainLayout_.addChild(engineRpmBar_);
    mainLayout_.addChild(engineRpmText_);
    mainLayout_.addChild(speedText_);
    mainLayout_.addChild(acceleration_);
    mainLayout_.addChild(brakePedal_);
    mainLayout_.addChild(gasPedal_);
    mainLayout_.addChild(linkState_);
    mainLayout_.addChild(textBox_);
    mainLayout_.addChild(testButton_);
}


void Entry::start() {
    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);
        tick();

        EndDrawing();
    }
    CloseWindow();
}

void Entry::tick() {
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    Vector2 touchPos {GetTouchPosition(0)};


    const qcpilot::shott::ConsoleFrame frame = qcpilot::platform::fetchConsoleFrame();
    engineRpmBar_.setRpm(frame.engineRpm);
    engineRpmText_.setRpm(frame.engineRpm);
    speedText_.setSpeed(frame.speedKph);
    acceleration_.setAcceleration(frame.ax, frame.ay);
    brakePedal_.setValue(frame.brake);
    gasPedal_.setValue(frame.gas);
    linkState_.setLastReceivedPacketElapsedMillis(qcpilot::platform::getLastReceivedElapsedMillis());
    char buffer[256];
    std::sprintf(buffer, "Touch [%d] %.2f, %.2f", GetTouchPointCount(), touchPos.x, touchPos.y);
    textBox_.setText(buffer);


    mainLayout_.renderAll(
      ui::ScreenViewport {0, 0, static_cast<std::size_t>(screenWidth), static_cast<std::size_t>(screenHeight)}, 1.0F);


    // DrawText(TextFormat("%lu", platform::getLastReceivedMillis()), 150, 50, 250, LIGHTGRAY);

    // if (GuiButton((Rectangle) {200, 300, 200, 80}, "Button 2")) {
    //     const qcpilot::shott::ConsoleFrame frame = qcpilot::shott::getConsoleFrame();
    //     count = frame.engineRpm;
    // }

    // const shott::ConsoleFrame frame = platform::fetchConsoleFrame();
    // // const qcpilot::shott::ConsoleFrame frame = qcpilot::shott::getConsoleFrame();
    // int count = frame.engineRpm;

    // char buffer[256];
    // std::sprintf(buffer, "Screen size: %d x %d", screenWidth, screenHeight);
    // DrawText(buffer, 190, 200, 80, LIGHTGRAY);
}

}    // namespace ui
}    // namespace qcpilot
