#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <vector>

#include "../ParseTree.h"
#include "../Statement.h"

namespace Astral
{
	class Program final : public Statement
	{
	private:
		std::vector<ParseTree*> statements;

	public:
		inline const std::vector<ParseTree*>& Statements() const { return statements; }

		void SetStatements(const std::vector<ParseTree*> statements) { this->statements = statements; }

		void Dump(int indent = 0) final override;

		Program(const Token& token) : Statement(token) {}
		~Program() override;
	};
}

#pragma warning(pop)