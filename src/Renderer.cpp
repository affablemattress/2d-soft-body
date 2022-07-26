#include "Config.h"

#include <raylib.h>

#include "Renderer.h"

uint16_t Renderer::kScreenWidth_ = SCREEN_WIDTH;
uint16_t Renderer::kScreenHeight_ = SCREEN_HEIGHT;
uint16_t Renderer::kPixelsPerUnit_ = PIXELS_PER_UNIT;

void Renderer::InitializeWindow() {
	InitWindow(SCREEN_HEIGHT, SCREEN_WIDTH, "2D Soft-Body");
	SetTargetFPS(TARGET_FPS);
}
void Renderer::CloseWindow() {
	CloseWindow();
}