#pragma once
#include "../RefCount.h"
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
		RefCount<Type::atype_t>* result;
	};
}