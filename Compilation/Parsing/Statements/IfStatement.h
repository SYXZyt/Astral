#pragma once
#include "../Statement.h"
#include "../Expression.h"

namespace Astral
{
	class IfStatement final : public Statement
	{
	private:
		Expression* ifExpression;
		Statement* ifBlock;

		//This may be null
		Statement* elseBlock;

	public:
		const Expression* IfExpression() const { return ifExpression; }

		const Statement* IfBlock() const { return ifBlock; }
		const Statement* ElseBlock() const { return elseBlock; }

		void Dump(int indent = 0) final override;

		IfStatement(const Token& token, Expression* ifExpression, Statement* ifBlock, Statement* elseBlock = nullptr) :
			Statement(token),
			ifExpression(ifExpression),
			ifBlock(ifBlock),
			elseBlock(elseBlock) {}

		~IfStatement() override;
	};
}