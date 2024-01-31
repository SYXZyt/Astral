#pragma once
#include <string>
#include <iomanip>
#include <iostream>
#include <windows.h>

#include "Astral.h"
#include "Compilation/Tokenisation/Token.h"

namespace Astral
{
	inline void Error(const char* const message, const Astral::Token& token)
	{
		std::string msg = message;
		msg += '\n';
		std::stringstream ss;
		ss << std::setw(4) << token.GetLexeme().line + 1;
		msg += ss.str() + "| " + token.GetLexeme().lexeme + '\n';
		msg += std::string(6, ' ');
		msg += std::string(token.GetLexeme().lexeme.size(), '^');

		msg += "\n\n";
		msg += "Occurred in " + token.GetLexeme().fname + " at line " + std::to_string(token.GetLexeme().line + 1) + " position " + std::to_string(token.GetLexeme().positionInLine + 1);

		if (UseCLIOutput)
			std::cerr << msg << "\n\n";
		else
			MessageBoxA(nullptr, msg.c_str(), "Astral encountered an error", MB_OK);
	}
}