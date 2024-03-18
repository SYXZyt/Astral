#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "../Statement.h"

#include <vector>

namespace Astral
{
	class StructDefinition final : public Statement
	{
	private:
		std::vector<Token> members;

	public:
		const std::vector<Token>& GetMembers() const { return members; }

		void AddMember(Token member) { members.push_back(member); }

		void Dump(int indent = 0) final override;

		StructDefinition(const Token& token) : Statement(token) {}
	};
}

#pragma warning(pop)