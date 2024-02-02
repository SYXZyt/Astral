#pragma once
#include "../ParseTree.h"
#include "../Expression.h"

namespace Astral
{
	class Literal final : public Expression
	{
	public:
		enum class LiteralType
		{
			NUMBER,
			BOOLEAN,
		};

		LiteralType type;
		void* data;

		void Dump(int indent = 0) final override;

		Literal(void* data, LiteralType type, const Token& token) : data(data), type(type), Expression(token) {}
		~Literal() override;
	};
}