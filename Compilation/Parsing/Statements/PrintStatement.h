#pragma once
#include "../Expression.h"
#include "../Statement.h"

namespace Astral
{
	class PrintStatement final : public Statement
	{
	private:
		Expression* expr;

	public:
		inline const Expression const* Expr() const { return expr; }

		void Dump(int indent = 0) final override;

		PrintStatement(const Token& token, Expression* expr) : expr(expr), Statement(token) {}
		~PrintStatement() override;
	};
}