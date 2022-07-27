#pragma once
#include <stdint.h>

class Component {
public:
	const enum Type{
		Transform = 0
	};
	Type GetType() const;
	uint32_t GetID() const;

	//All components must have a type.
	Component(Type type);
	~Component();
protected:
	const Type type_;
private:
	const uint32_t kID_;
};

