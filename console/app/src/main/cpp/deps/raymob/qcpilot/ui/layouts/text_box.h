#ifndef __QCPILOT_UI_LAYOUTS_TEXT_BOX_H__
#define __QCPILOT_UI_LAYOUTS_TEXT_BOX_H__

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "qcpilot/ui/layouts/absolute_layout.h"
#include "raylib.h"


namespace qcpilot {
namespace ui {

class TextBox : public AbsoluteLayout {
public:
  TextBox(CanvasArea canvasArea) : AbsoluteLayout {canvasArea} {
    buffer_[0] = '\0';
  }

  void setText(const char *text) {
    std::strncpy(buffer_, text, 1023);
    buffer_[1023] = '\0';
  }

  void render() override {
    rectangle(ui::CanvasArea {0, 0, canvasArea_.w, canvasArea_.h}, BLACK);
    text(buffer_, canvasArea_.h / 4, canvasArea_.h / 4, canvasArea_.h / 2, WHITE);
  }

private:
  char buffer_[1024];
};
}    // namespace ui
}    // namespace qcpilot
#endif
