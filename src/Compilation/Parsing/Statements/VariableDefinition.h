#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "../Statement.h"
#include "../Expression.h"

namespace Astral
{
	class VariableDefinition final : public Statement
	{
	private:
		Expression* expr;
		Token name;

	public:
		inline const Expression* Expr() const { return expr; }
		inline const Token& Name() const { return name; }

		void Dump(int indent = 0) final override;

		VariableDefinition(const Token& token, const Token& name, Expression* expr) : name(name), expr(expr), Statement(token) {}
		~VariableDefinition();
	};
}

#pragma warning(pop)