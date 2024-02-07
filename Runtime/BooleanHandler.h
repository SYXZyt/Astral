#pragma once
#include <memory>

#include "Result.h"
#include "../Astral.h"
#include "Types/AstralTypes.h"

namespace Astral::Boolean
{
	extern result_t Equality(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t Nequality(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t Greater(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t GreaterEquals(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t Less(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t LessEquals(std::shared_ptr<Type::atype_t> lhs, std::shared_ptr<Type::atype_t> rhs);
	extern result_t Not(std::shared_ptr<Type::atype_t> val);
}