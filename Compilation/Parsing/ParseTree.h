#pragma once
#include <iostream>

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

		virtual void Dump(int indent = 0);

		ParseTree(const Token& token) : token(token) {}
		virtual ~ParseTree() {}
	};
}