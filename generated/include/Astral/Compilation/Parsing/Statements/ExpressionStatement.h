#pragma once
#include "../Statement.h"
#include "../Expression.h"

namespace Astral
{
	class ExpressionStatement final : public Statement
	{
	private:
		Expression* expr;

	public:
		inline const Expression* GetExpression() const { return expr; }

		void Dump(int indent = 0) final override;

		ExpressionStatement(Expression* expr) : Statement(expr->GetToken()), expr(expr) {}
		~ExpressionStatement();
	};
}