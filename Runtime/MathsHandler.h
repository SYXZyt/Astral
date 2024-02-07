#pragma once
#include <memory>

#include "Result.h"
#include "../Astral.h"
#include "Types/AstralTypes.h"

namespace Astral::Maths
{
	extern result_t Addition(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t Subtraction(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t Multiplication(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t Divide(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t Power(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t Modulo(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t Minus(std::shared_ptr<Type::atype_t> val);
}