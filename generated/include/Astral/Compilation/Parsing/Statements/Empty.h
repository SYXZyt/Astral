#pragma once
#include "../Statement.h"

namespace Astral
{
	class Empty final : public Statement
	{
	public:
		void Dump(int indent = 0) final override;

		Empty(const Token& token) : Statement(token) {}
	};
}