#pragma once
#include <ostream>

#include "../../Astral.h"

namespace Astral
{
	enum class ASTRAL TokenType
	{
		_EOF,
		NUMBER,
		PLUS,
		MINUS,
		ASTERISK,
		DIVIDE,
	};

	ASTRAL inline std::ostream& operator<<(std::ostream& os, const TokenType& t)
	{
		switch (t)
		{
		case TokenType::NUMBER:
			os << "<NUMBER>";
			break;
		default:
			os << "<UNKNOWN-TYPE>";
			break;
		}

		return os;
	}
}