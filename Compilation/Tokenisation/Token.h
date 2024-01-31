#pragma once
#include <ostream>

#include "Lexeme.h"
#include "TokenType.h"

#include "../../Astral.h"

namespace Astral
{
	class ASTRAL Token final
	{
	private:
		Lexeme lexeme;
		TokenType type;

	public:
		const Lexeme& GetLexeme() const { return lexeme; }
		TokenType GetType() const { return type; }

		inline void SetLexeme(const Lexeme& l) { lexeme = l; }
		inline void SetType(TokenType t) { type = t; }

		Token() = default;
		Token(const Lexeme& lexeme, TokenType type) : lexeme(lexeme), type(type) {}
		Token(const Lexeme&& lexeme, TokenType type) : lexeme(lexeme), type(type) {}
	};

	ASTRAL inline std::ostream& operator<<(std::ostream& os, const Token& t)
	{
		os << "[" << t.GetLexeme() << ' ' << t.GetType() << "]";
		return os;
	}
}