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

		void Dump(int indent = 0) final override;

		Grouping(Expression* expression, const Token& token) : expression(expression), Expression(token) {}
		~Grouping();
	};
}