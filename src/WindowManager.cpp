#include "WindowManager.h"

#include <stdint.h>
#include <raylib.h>
#include <raygui.h>

namespace Patchwork {
    void WindowManager::InitializeWindow(uint16_t screenWidth, uint16_t screenHeight, const char* title, uint16_t targetFPS) {
        InitWindow(screenWidth, screenHeight, title);
        SetTargetFPS(targetFPS);
    }
    void WindowManager::CloseWindow() {
        CloseWindow();
    }
}