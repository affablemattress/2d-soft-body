#include "GameObject.h"
#include "Config.h"
#include "UniqueID.h"

uint32_t GameObject::GetID() const { return kID_; }
Transform* GameObject::GetTransform() const {
	return transform_;
}
void GameObject::SetTransform(Transform* transform) {
	delete transform_;
	transform_ = transform;
}
void GameObject::DeleteTransform() {
	delete transform_;
	transform_ = 0;
}

GameObject::GameObject(V2 position, double rotation) 
	: kID_(UniqueID::GenerateID()) {
	transform_ = new Transform();
}
GameObject::GameObject() 
	: kID_(UniqueID::GenerateID()) {
}
GameObject::~GameObject() {
	delete transform_;
};
