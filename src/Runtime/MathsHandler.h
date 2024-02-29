#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "Result.h"
#include "../Astral.h"
#include "Types/AstralTypes.h"

namespace Astral::Maths
{
	extern result_t Addition(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Subtraction(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Multiplication(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Divide(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Power(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Modulo(Type::atype_t* lhs, Type::atype_t* rhs);
	extern result_t Minus(Type::atype_t* val);
	extern result_t Factorial(Type::atype_t* val);
}

#pragma warning(pop)