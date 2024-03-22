#pragma once
#include "../Statement.h"

namespace Astral
{
	class Break final : public Statement
	{
	public:
		void Dump(int indent = 0) final override;

		Break(const Token& token) : Statement(token) {}
	};
}