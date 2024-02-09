#pragma once
#include <vector>

#include "../Expression.h"

namespace Astral
{
	class Factorial final : public Expression
	{
	private:
		Expression* expr;

	public:
		inline Expression* GetExpression() { return expr; }

		void Dump(int indent = 0) final override;

		Factorial(Expression* expr, const Token& token) : expr(expr), Expression(token) {}
		~Factorial() override;
	};
}