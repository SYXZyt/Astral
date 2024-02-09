#pragma once
#include "../Expression.h"

namespace Astral
{
	class IncrementExpression final : public Expression
	{
	private:
		bool isPrefix;
		Expression* expression;

	public:
		bool IsPrefix() const { return isPrefix; }
		const Expression* GetExpression() const { return expression; }

		void Dump(int indent = 0) final override;

		IncrementExpression(Expression* expression, bool isPrefix, const Token& token) : expression(expression), isPrefix(isPrefix), Expression(token) {}
		~IncrementExpression();
	};
}