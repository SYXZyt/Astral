#pragma once
#include <vector>

#include "../Statement.h"

namespace Astral
{
	class Block final : public Statement
	{
	private:
		std::vector<Statement*> statements;

	public:
		inline const std::vector<Statement*>& Statements() const { return statements; }

		void SetStatements(const std::vector<Statement*> statements) { this->statements = statements; }

		void Dump(int indent = 0) final override;

		Block(const Token& token) : Statement(token) {}
		~Block() override;
	};
}