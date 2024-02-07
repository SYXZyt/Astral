#pragma once
#include <memory>

#include "../../Astral.h"
#include "../Types/AstralTypes.h"

namespace Astral
{
	class ASTRAL Variable final
	{
	private:
		char* varname;
		std::shared_ptr<Type::atype_t> value;

	public:
		inline const char* Name() const { return varname; }
		inline std::shared_ptr<Type::atype_t> Value() { return value; }

		inline void SetValue(std::shared_ptr<Type::atype_t> value)
		{
			this->value = value;
		}

		Variable(const char* name, std::shared_ptr<Type::atype_t> value);
		~Variable();
	};
}