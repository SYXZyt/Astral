#pragma once
#include "../Tokenisation/Token.h"

#include "../../Astral.h"

namespace Astral
{
	class ASTRAL ParseTree
	{
	protected:
		Token token;

	public:
		const Token& GetToken() const { return token; }

		ParseTree(const Token& token) : token(token) {}
		virtual ~ParseTree() {}
	};
}