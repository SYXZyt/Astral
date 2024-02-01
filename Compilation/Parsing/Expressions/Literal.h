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
		};

		LiteralType type;
		void* data;

		Literal(void* data, LiteralType type, const Token& token) : data(data), type(type), Expression(token) {}
		~Literal() override;
	};
}