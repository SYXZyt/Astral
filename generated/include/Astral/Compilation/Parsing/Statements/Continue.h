#pragma once
#include "../Statement.h"

namespace Astral
{
	class Continue final : public Statement
	{
	public:
		void Dump(int indent = 0) final override;

		Continue(const Token& token) : Statement(token) {}
	};
}