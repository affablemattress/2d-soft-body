#pragma once
#include <stdint.h>

class Renderer{
	static uint16_t kScreenWidth_;
	static uint16_t kScreenHeight_;
	static uint16_t kPixelsPerUnit_;
public:
	static void InitializeWindow();
	static void CloseWindow();
	/*Draw function which must be implemented by each drawable object type.*/
	virtual void Draw() = 0;
};

