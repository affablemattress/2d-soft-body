#pragma once
#include "V2.h"
#include "Component.h"

class Transform : public Component {
public:
	V2 GetPosition() const;
	void SetPosition(const V2& position);
	double GetRotation() const;
	void SetRotation(double rotation);
	
	Transform(V2 position, double rotation);
	Transform();
	~Transform();
private:
	V2 position_;
	double rotation_;
};

