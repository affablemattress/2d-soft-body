#pragma once
#include <stdint.h>
#include "V2.h"

//Entity class/component which holds the objects transform and unique ID. Every object must inherit Entity class.
class Entity {
	static uint32_t lastID_;
	const uint32_t kID_;
	V2 position_;
public:
	uint32_t GetID();
	V2 GetPosition();
	void SetPosition(const V2& position );

	Entity(V2 position);
	Entity();
	~Entity();
};

