#pragma once
#include "V2.h"
#include "Component.h"
#include "Transform.h"

#include <stdint.h>

class GameObject {
	const uint32_t kID_;
	Transform* transform_;
public:
	uint32_t GetID() const;

	Transform* GetTransform() const;
	void SetTransform(Transform* component);
	void DeleteTransform();

	GameObject(V2 position, double rotation);
	GameObject();
	~GameObject();
};

