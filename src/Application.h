#pragma once
#include <stdint.h>

namespace Shabby {
	class Application {
	public:
		void Run();

		Application(uint16_t screenWidth, uint16_t screenHeight, const char* title, uint16_t targetFPS);
		virtual ~Application();
	private: 
		uint16_t screenWidth_;
		uint16_t screenHeight_;
		const char* title_;
		uint16_t targetFPS_;
	};
}