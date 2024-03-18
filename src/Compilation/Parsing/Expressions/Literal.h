#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

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
			STRING,
			IDENTIFER,
			REFERENCE,
			STRUCT_ACCESS,
			STRUCT_ACCESS_LEAF, //Final node in a struct access
			STRUCT_ACCESS_ROOT, //First node in a struct access
			STRUCT_ACCESS_LERT, //Node is both a root and leaf, hence LERT: LEaf-RooT
		};

		LiteralType type;
		void* data;

		void Dump(int indent = 0) final override;

		Literal(void* data, LiteralType type, const Token& token) : data(data), type(type), Expression(token) {}
		~Literal() override;
	};
}

#pragma warning(pop)