#pragma once
#include "Entity.h"
#include "Renderer.h"

class Circle : public Entity, public Renderer {
	Circle(V2 position);
	Circle();
	~Circle();
};

