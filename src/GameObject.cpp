#include "GameObject.h"

#include "UniqueID.h"

namespace Shabby {
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

	GameObject::GameObject(const V2& position, double rotation)
		: kID_(UniqueID::GenerateID())
		, transform_(new Transform()) {}
	GameObject::GameObject()
		: kID_(UniqueID::GenerateID())
		, transform_(0) {}
	GameObject::~GameObject() {
		delete transform_;
	};
}

