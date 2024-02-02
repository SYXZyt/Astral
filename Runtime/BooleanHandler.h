#pragma once
#include "../Astral.h"
#include "Types/AstralTypes.h"

namespace Astral::Boolean
{
	extern Type::atype_t* Equality(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* Nequality(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* Greater(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* GreaterEquals(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* Less(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* LessEquals(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* Not(Type::atype_t* val);
}