#pragma once
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <windows.h>

#include "Astral.h"
#include "Compilation/Tokenisation/Token.h"

namespace Astral
{
	inline int StringLengthConvertTabToSpace(const char* message, int stop = -1, int spaceCount = 2)
	{
		int count = 0;
		int len = (int)strlen(message);

		for (int i = 0; i < len; ++i)
		{
			if (i >= stop && stop > -1)
				break;

			if (message[i] == '\t')
				count += spaceCount;
			else
				++count;
		}

		return count;
	}

	inline void Error(const char* const message)
	{
		if (UseCLIOutput)
			std::cerr << message << "\n\n";
		else
			MessageBoxA(nullptr, message, "Astral encountered an error", MB_OK);
	}

	inline void Error(const char* const message, const Astral::Lexeme& lexeme)
	{
		std::string msg = message;
		msg += '\n';
		std::stringstream ss;
		ss << std::setw(4) << lexeme.line + 1;
		msg += ss.str() + "| " + lexeme.lineData + '\n';

		msg += std::string(StringLengthConvertTabToSpace(lexeme.lineData.c_str(), lexeme.positionInLine) + 6, ' ');
		msg += std::string(lexeme.lexeme.size(), '^');

		msg += "\n\n";
		msg += "Occurred in " + lexeme.fname + " at line " + std::to_string(lexeme.line + 1) + " position " + std::to_string(lexeme.positionInLine + 1);

		if (UseCLIOutput)
			std::cerr << msg << "\n\n";
		else
			MessageBoxA(nullptr, msg.c_str(), "Astral encountered an error", MB_OK);
	}

	inline void Error(const char* const message, const Astral::Token& token)
	{
		Error(message, token.GetLexeme());
	}
}