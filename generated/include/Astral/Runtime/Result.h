#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

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
			R_VOID_REFERENCE,
		};

		ResultType type;
		Type::atype_t* result;
	};
}

#pragma warning(pop)