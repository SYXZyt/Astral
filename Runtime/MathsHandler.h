#pragma once
#include "../Astral.h"
#include "Types/AstralTypes.h"

namespace Astral::Maths
{
	extern Type::atype_t* Addition(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* Subtraction(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* Multiplication(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* Divide(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* Power(Type::atype_t* lhs, Type::atype_t* rhs);
	extern Type::atype_t* Minus(Type::atype_t* val);
}