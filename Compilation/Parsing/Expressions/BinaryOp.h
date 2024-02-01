#pragma once
#include "../ParseTree.h"
#include "../Expression.h"

namespace Astral
{
	class BinaryOp final : public Expression
	{
	private:
		Expression* lhs;
		Expression* rhs;

	public:
		inline const Expression* Lhs() const { return lhs; }
		inline const Expression* Rhs() const { return rhs; }

		void Dump(int indent = 0) final override;

		BinaryOp(Expression* lhs, Token op, Expression* rhs) : lhs(lhs), rhs(rhs), Expression(op) {}
		~BinaryOp() override;
	};
}