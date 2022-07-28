#pragma once
#include "V2.h"
#include "Component.h"
#include "Transform.h"

#include <stdint.h>

namespace Patchwork {
	class GameObject {
	public:
		uint32_t GetID() const;
		Transform* GetTransform() const;
		//Sets GameObject's Transform compnent to the one passed by parameter and deletes the old one.
		void SetTransform(Transform* component);
		void DeleteTransform();

		GameObject();
		~GameObject();
	private: 
		const uint32_t kID_;
		Transform* transform_;
	};
}
