#pragma once
#include "V2.h"
#include "Component.h"

namespace Patchwork {
	class Transform : public Component {
	public:
		Component::Type GetType() const;
		V2 GetPosition() const;
		void SetPosition(const V2& position);
		double GetRotation() const;
		//Set GameObject's rotation to mod(input, 360).
		void SetRotation(double rotation);

		Transform(const V2& position, double rotation);
		//@returns Transform with position (0, 0) and rotation 0
		Transform();
		~Transform();
	private:
		V2 position_;
		double rotation_;
	};
}

