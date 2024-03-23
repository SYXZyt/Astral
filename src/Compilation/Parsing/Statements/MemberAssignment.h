#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "../Statement.h"
#include "../Expression.h"
#include "VariableAssignment.h"
#include "../Expressions/Literal.h"

namespace Astral
{
	class MemberAssignment final : public Statement
	{
	private:
		Expression* expr;
		Literal* structMember;
		VariableAssignment* va; //This is only stored so I don't have to deal with copying its expression.

	public:
		inline const Expression* Expr() const { return expr; }
		inline const Literal* Member() const { return structMember; }

		void Dump(int indent = 0) final override;

		MemberAssignment(const Token& token, Literal* structMember, VariableAssignment* va) : structMember(structMember), va(va), expr(va->Expr()), Statement(token) {}
		~MemberAssignment();
	};
}

#pragma warning(pop)