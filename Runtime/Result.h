#pragma once
#include "Types/AstralTypes.h"

namespace Astral
{
	struct result_t
	{
		enum class ResultType
		{
			R_OK,
			R_FAIL,
			R_DIV_BY_ZERO,
			R_INVALID_TYPES,
		};

		ResultType type;
		std::shared_ptr<Type::atype_t> result;
	};
}