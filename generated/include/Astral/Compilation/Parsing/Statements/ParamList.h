#pragma once
#include <vector>

#include "../Statement.h"

namespace Astral
{
	class ParamList final : public Statement
	{
	private:
		std::vector<Lexeme> declarations;

	public:
		inline const std::vector<Lexeme>& GetDeclarations() const { return declarations; };

		void Dump(int indent = 0) final override;

		ParamList(const Token& token, const std::vector<Lexeme> declarations) : declarations(declarations), Statement(token) {}
	};
}