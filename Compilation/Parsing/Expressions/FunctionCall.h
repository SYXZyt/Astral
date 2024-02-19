#pragma once
#include "CallParameters.h"
#include "../Expression.h"

namespace Astral
{
	class FunctionCall final : public Expression
	{
	private:
		CallParameters* parameters;

	public:
		inline const CallParameters* GetParameters() const { return parameters; }

		void Dump(int indent = 0) final override;

		FunctionCall(const Token& token, CallParameters* parameters) : Expression(token), parameters(parameters) {}
		~FunctionCall();
	};
}