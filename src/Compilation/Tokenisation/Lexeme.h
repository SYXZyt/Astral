#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

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
		std::string lineData;

		Lexeme() :
			positionInBuffer(0),
			positionInLine(0),
			line(0),
			lexeme(""),
			fname(""),
			lineData("")
		{}
		Lexeme(const Lexeme& other) = default;
	};

	ASTRAL inline std::ostream& operator<<(std::ostream& os, const Lexeme& l)
	{
		os << "<" << l.lexeme << " " << l.line + 1 << ", " << l.positionInLine + 1 << ", '" << l.fname << "'>";
		return os;
	}
}

#pragma warning(pop)