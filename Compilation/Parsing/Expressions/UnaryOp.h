#pragma once
#include "Literal.h"
#include "../ParseTree.h"
#include "../Expression.h"

namespace Astral
{
	class UnaryOp final : public Expression
	{
	private:
		Token op;
		Expression* value;

	public:
		void Dump(int indent = 0) final override;

		UnaryOp(const Token& op, Expression* value) : op(op), value(value), Expression(op) {}
		~UnaryOp();
	};
}