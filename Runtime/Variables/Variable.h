#pragma once
#include "../../Astral.h"
#include "../Types/AstralTypes.h"

namespace Astral
{
	class ASTRAL Variable final
	{
	private:
		char* varname;
		Type::atype_t* value;

	public:
		inline const char* Name() const { return varname; }
		inline Type::atype_t* Value() { return value; }

		inline void SetValue(Type::atype_t* value)
		{
			if (this->value)
				delete this->value;

			this->value = value;
		}

		Variable(const char* name, Type::atype_t* value);
		~Variable();
	};
}