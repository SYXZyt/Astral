#pragma once
#include "Block.h"
#include "ParamList.h"
#include "../Statement.h"

namespace Astral
{
	class Function final : public Statement
	{
	private:
		Token funcName;
		ParamList* parameters;
		Block* funcBody;

	public:
		const Token& GetName() const { return funcName; }
		const ParamList* GetParamList() const { return parameters; }
		const Block* GetBody() const { return funcBody; }

		void Dump(int indent = 0) final override;

		Function(const Token& token, const Token& funcName, ParamList* parameters, Block* funcBody) :
			Statement(token),
			funcName(funcName),
			parameters(parameters),
			funcBody(funcBody) {}
	};
}