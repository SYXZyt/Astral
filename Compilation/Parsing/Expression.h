#pragma once
#include "ParseTree.h"

namespace Astral
{
	class Expression : public ParseTree
	{
	public:
		virtual void Dump(int indent = 0) override;

		Expression(const Token& token) : ParseTree(token) {}
	};
}