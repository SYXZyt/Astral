#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "Token.h"

#include "../../Astral.h"
#include "../../ErrorManager.h"

namespace Astral
{
	class ASTRAL Lexer final
	{
	private:
		filepos bufferpos;
		filepos posOnLine;
		filepos line;
		char currentChar;

		bool failed;

		std::string fname;
		std::string data;

		std::vector<Token> tokens;

		Token EofToken();

		void Advance(int count);
		void Advance();

		char Peek();

		Token GenerateNumber();
		Token GenerateString(char strChar);
		Token GenerateIdentifier();

		std::string GetLineData(filepos linenum);

	public:
		inline bool Failed() const { return failed; }
		inline const std::vector<Token>& GetTokens() const { return tokens; }

		void Tokenise();

		Lexer() = delete;
		Lexer(const std::string& data, const std::string& fname);
	};
}

#pragma warning(pop)