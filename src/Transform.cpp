#include "Transform.h"
#include "Component.h"

V2 Transform::GetPosition() const { return position_; }
void Transform::SetPosition(const V2& position) {
	position_ = position;
}
double Transform::GetRotation() const { return rotation_; }
void Transform::SetRotation(double rotation) {
	rotation_ = rotation;
}

Transform::Transform(V2 position, double rotation) 
	: position_(position), rotation_(rotation), Component(Component::Type::Transform) {}
Transform::Transform() 
	: position_(V2(0, 0)), rotation_(0), Component(Component::Type::Transform) {}
Transform::~Transform() {}