#include "qcpilot/ui/entry.h"
#include <cstdio>
#include <vector>
#include "qcpilot/ui/input/touch_manager.h"
#include "qcpilot/ui/layouts/engine_rpm_bar.h"
#include "qcpilot/ui/layouts/fitting_layout.h"
#include "qcpilot/ui/layouts/pedal.h"
#include "qcpilot/ui/platform.h"
#include "raylib.h"
#include "raymob/qcpilot/ui/settings.h"


namespace qcpilot {
namespace ui {

namespace {
char infoText[256];
}

Entry::Entry(int width, int height) :
    touchManager_ {},
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
    meterButton_ {ui::CanvasArea {800U, 50U, 130U, 50U}},
    meterIndicator_ {ui::CanvasArea {940U, 50U, 7U, 50U}},
    adasButton_ {ui::CanvasArea {800U, 125U, 130U, 50U}},
    adasIndicator_ {ui::CanvasArea {940U, 125U, 7U, 50U}},
    panelState_ {0} {
  InitWindow(width, height, "raylib [core] example - basic window");
  SetTargetFPS(60);    // Set our game to run at 60 frames-per-second


  // speedText_.setBackgroundColor(RED);
  // acceleration_.setBackgroundColor(DARKBLUE);
  // brakePedal_.setBackgroundColor(VIOLET);
  // gasPedal_.setBackgroundColor(LIME);

  mainLayout_.setBackgroundColor(kBackground);
  mainLayout_.addChild(engineRpmBar_);
  mainLayout_.addChild(engineRpmText_);
  mainLayout_.addChild(speedText_);
  mainLayout_.addChild(acceleration_);
  mainLayout_.addChild(brakePedal_);
  mainLayout_.addChild(gasPedal_);
  mainLayout_.addChild(linkState_);
  mainLayout_.addChild(textBox_);
  mainLayout_.addChild(meterButton_);
  mainLayout_.addChild(meterIndicator_);
  mainLayout_.addChild(adasButton_);
  mainLayout_.addChild(adasIndicator_);

  meterButton_.setText("Sport");
  meterIndicator_.setEnabled(true);
  adasButton_.setText("ADAS");
  adasIndicator_.setEnabled(false);

  meterButton_.setPushDownCallback([this]() {
    std::sprintf(infoText, "Meter button pushed down");
    this->panelState_ = 0;
  });
  adasButton_.setPushDownCallback([this]() {
    std::sprintf(infoText, "ADAS button pushed down");
    this->panelState_ = 1;
  });
}


void Entry::start() {
  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(kBackground);
    tick();

    EndDrawing();
  }
  CloseWindow();
}

void Entry::tick() {
  int screenHeight = GetScreenHeight();
  int screenWidth = GetScreenWidth();

  const qcpilot::shott::ConsoleFrame frame = qcpilot::platform::fetchConsoleFrame();
  const std::uint64_t lastReceivedMillis = qcpilot::platform::getLastReceivedElapsedMillis();
  const std::vector<qcpilot::platform::ui::KeyboardEvent> keyboardEvents = qcpilot::platform::fetchKeyboardEvents();

  for (const auto &evt : keyboardEvents) {
    std::sprintf(infoText,
                 "Key[%d] %s",
                 evt.keyCode,
                 evt.type == qcpilot::platform::ui::KeyboardEvent::Type::KeyDown ? "down"
                 : evt.type == qcpilot::platform::ui::KeyboardEvent::Type::KeyUp ? "up"
                                                                                 : "repeat");
  }


  touchManager_.tick();
  TouchManager::TouchEvent touchEvent = touchManager_.getTouchEvent();
  bool touchHandled = mainLayout_.handleTouchEvent(touchEvent);


  engineRpmBar_.setRpm(frame.engineRpm);
  engineRpmText_.setRpm(frame.engineRpm);
  speedText_.setSpeed(frame.speedKph);
  acceleration_.setAcceleration(frame.ax, frame.ay);
  brakePedal_.setValue(frame.brake);
  gasPedal_.setValue(frame.gas);
  linkState_.setLastReceivedPacketElapsedMillis(lastReceivedMillis);

  textBox_.setText(infoText);
  meterIndicator_.setEnabled(panelState_ == 0);
  adasIndicator_.setEnabled(panelState_ == 1);


  mainLayout_.renderAll(
    ui::ScreenViewport {0, 0, static_cast<std::size_t>(screenWidth), static_cast<std::size_t>(screenHeight)}, 1.0F);
}

}    // namespace ui
}    // namespace qcpilot
