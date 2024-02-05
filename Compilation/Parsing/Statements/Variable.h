#pragma once
#include "../Statement.h"
#include "../Expression.h"

namespace Astral
{
	class Variable final : public Statement
	{
	private:
		Expression* expr;
		Token name;

	public:
		inline const Expression const* Expr() const { return expr; }
		inline const Token& Name() const { return name; }

		void Dump(int indent = 0) final override;

		Variable(const Token& token, const Token& name, Expression* expr) : name(name), expr(expr), Statement(token) {}
		~Variable();
	};
}