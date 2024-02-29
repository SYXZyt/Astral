#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "../Statement.h"
#include "../Expression.h"

namespace Astral
{
	class VariableAssignment final : public Statement
	{
	private:
		Expression* expr;

	public:
		inline const Expression* Expr() const { return expr; }

		void Dump(int indent = 0) final override;

		VariableAssignment(const Token& token, Expression* expr) : expr(expr), Statement(token) {}
		~VariableAssignment();
	};
}

#pragma warning(pop)