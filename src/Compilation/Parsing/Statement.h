#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "ParseTree.h"

namespace Astral
{
	class Statement : public ParseTree
	{
	public:
		virtual void Dump(int indent = 0) override;

		Statement(const Token& token) : ParseTree(token) {}
	};
}

#pragma warning(pop)