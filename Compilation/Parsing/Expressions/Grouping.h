#pragma once
#include "../Expression.h"

namespace Astral
{
	class Grouping final : public Expression
	{
	private:
		Expression* expression;

	public:
		inline Expression* GetExpression() { return expression; }

		Grouping(Expression* expression, const Token& token) : expression(expression), Expression(token) {}
		~Grouping();
	};
}