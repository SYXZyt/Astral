#pragma once
#include <vector>

#include "../Statement.h"

namespace Astral
{
	class ParamList final : public Statement
	{
	private:
		std::vector<Statement*> declarations;

	public:
		inline const std::vector<Statement*>& GetDeclarations() const { return declarations; };

		void Dump(int indent = 0) final override;

		ParamList(const Token& token, const std::vector<Statement*> declarations) : declarations(declarations), Statement(token) {}
		~ParamList();
	};
}