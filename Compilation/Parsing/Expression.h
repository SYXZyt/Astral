#pragma once
#include "ParseTree.h"

namespace Astral
{
	class Expression : public ParseTree
	{
	public:
		Expression(const Token& token) : ParseTree(token) {}
	};
}