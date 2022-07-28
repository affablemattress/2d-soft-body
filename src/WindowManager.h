#pragma once
#include <stdint.h>

namespace Shabby {
	class WindowManager
	{
	public:
		static void InitializeWindow(uint16_t screenWidth, uint16_t screenHeight, const char* title, uint16_t targetFPS);
		static void CloseWindow();
	};
}

