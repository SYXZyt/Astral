#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "Result.h"
#include "../Astral.h"
#include "Types/AstralTypes.h"

namespace Astral::Boolean
{
	extern result_t Equality(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Nequality(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Greater(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t GreaterEquals(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Less(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t LessEquals(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t And(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Or(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Not(Type::atype_t* val);
}

#pragma warning(pop)