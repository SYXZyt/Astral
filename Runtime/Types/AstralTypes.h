#pragma once
#include "../../Astral.h"

namespace Astral::Type
{
	class ASTRAL atype_t
	{
	public:
		virtual ~atype_t() {}
	};

	class ASTRAL number_t final : public atype_t
	{
	private:
		float value;

	public:
		inline float Value() const { return value; }
		inline void SetValue(float value) { this->value = value; }

		number_t() : value(0.0f), atype_t() {}
		number_t(float v) : value(v), atype_t() {}
		~number_t() final override {}
	};
}