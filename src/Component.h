#pragma once
#include <stdint.h>

namespace Shabby {
	class Component {
	public:
		const enum Type{
			Transform = 0
		};
		Type GetType() const;
		uint32_t GetID() const;

		//All components must have a type.
		Component(const Type& type);
		virtual ~Component();
	protected:
		const Type type_;
	private:
		const uint32_t kID_;
	};
}

