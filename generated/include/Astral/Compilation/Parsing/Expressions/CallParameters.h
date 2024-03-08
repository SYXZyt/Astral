#pragma once
#include <vector>

#include "../Expression.h"

namespace Astral
{
	class CallParameters final : public Expression
	{
	private:
		std::vector<Expression*> params;

	public:
		inline const std::vector<Expression*>& GetParameters() const { return params; }

		void Dump(int indent = 0) final override;

		CallParameters(const Token& token, const std::vector<Expression*>& params) : Expression(token), params(params) {}
		~CallParameters() override;
	};
}