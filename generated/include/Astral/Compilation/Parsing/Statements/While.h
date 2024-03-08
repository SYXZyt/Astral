#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "../Statement.h"
#include "../Expression.h"

namespace Astral
{
	class While : public Statement
	{
	private:
		Expression* loopCondition;
		Statement* body;

	public:
		inline const Expression* GetCondition() const { return loopCondition; }
		inline const Statement* GetBody() const { return body; }

		void Dump(int indent = 0) override final;

		While(const Token& token, Expression* loopCondition, Statement* body) : loopCondition(loopCondition), body(body), Statement(token) {}
		~While();
	};
}

#pragma warning(pop)