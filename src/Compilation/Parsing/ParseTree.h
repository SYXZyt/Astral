#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

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

#pragma warning(pop)