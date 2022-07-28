#include "Transform.h"

#include "Component.h"

#include <math.h>

namespace Patchwork {
	Component::Type Transform::GetType() const { return Component::Type::Transform; }
	V2 Transform::GetPosition() const { return position_; }
	void Transform::SetPosition(const V2& position) {
		position_ = position;
	}
	double Transform::GetRotation() const { return rotation_; }
	void Transform::SetRotation(double rotation) {
		rotation_ = fmod(rotation, 360);
	}

	Transform::Transform(const V2& position, double rotation)
		: position_(position), rotation_(rotation) {}
	Transform::Transform()
		: position_(V2(0, 0)), rotation_(0) {}
	Transform::~Transform() {}
}
