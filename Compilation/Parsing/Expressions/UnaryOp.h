#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

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
		const Expression* GetExpression() const { return value; }

		void Dump(int indent = 0) final override;

		UnaryOp(const Token& op, Expression* value) : op(op), value(value), Expression(op) {}
		~UnaryOp();
	};
}

#pragma warning(pop)