#pragma once
#include <string>
#include <ostream>

#include "../../Types.h"
#include "../../Astral.h"

namespace Astral
{
	struct ASTRAL Lexeme final
	{
		filepos positionInBuffer;
		filepos positionInLine;
		filepos line;
		
		std::string lexeme;
		std::string fname;
	};

	ASTRAL inline std::ostream& operator<<(std::ostream& os, const Lexeme& l)
	{
		os << "<" << l.lexeme << " " << l.line + 1 << ", " << l.positionInLine + 1 << ", '" << l.fname << "'>";
		return os;
	}
}