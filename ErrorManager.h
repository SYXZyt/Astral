#pragma once
#include <string>
#include <windows.h>

#include "Compilation/Tokenisation/Token.h"

namespace Astral
{
	inline void Error(const char* const message, const Astral::Token& token)
	{
		std::string msg = message;
		msg += "\n";
		msg += "Occurred at '" + token.GetLexeme().lexeme + "' in " + token.GetLexeme().fname + " at line " + std::to_string(token.GetLexeme().line + 1) + " position " + std::to_string(token.GetLexeme().positionInLine + 1);

		MessageBoxA(nullptr, msg.c_str(), "Astral encountered an error", MB_OK);
	}
}