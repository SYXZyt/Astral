#pragma once
#include "../Statement.h"
#include "../Expression.h"

namespace Astral
{
	class Return final : public Statement
	{
	private:
		Expression* returnValue;

	public:
		inline const Expression* GetReturnValue() const { return returnValue; }

		void Dump(int indent = 0) final override;

		Return(const Token& token, Expression* returnValue) : Statement(token), returnValue(returnValue) {}
		~Return() override;
	};
}