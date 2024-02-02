#pragma once
#include "../Astral.h"
#include "Types/AstralTypes.h"

namespace Astral::Boolean
{
	extern Type::atype_t* Equality(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* Nequality(Type::atype_t* lhs, Type::atype_t* rhs);
}