#pragma once
#include "../../Astral.h"
#include "../../RefCount.h"
#include "../Types/AstralTypes.h"

namespace Astral
{
	class ASTRAL Variable final
	{
	private:
		char* varname;
		RefCount<Type::atype_t>* value;

	public:
		inline const char* Name() const { return varname; }
		inline RefCount<Type::atype_t>* Value() { return value; }

		inline void SetValue(Type::atype_t* value)
		{
			this->value->Update(value);
		}

		Variable(const char* name, RefCount<Type::atype_t>* value);
		~Variable();
	};
}