#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "Interpreter.h"
#include "../Compilation/Tokenisation/Lexeme.h"

namespace Astral
{
	namespace Type { class Type::atype_t; }

	namespace Functions
	{
		namespace Astral
		{
			extern Type::atype_t* GetType(FuncParams params, Interpreter& vm, const Lexeme& caller);
			extern Type::atype_t* CreateVoid(FuncParams params, Interpreter& vm, const Lexeme& caller);

			namespace IO
			{
				extern Type::atype_t* PrintFunction(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* PrintlnFunction(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Input(FuncParams params, Interpreter& vm, const Lexeme& caller);
			}

			namespace String
			{
				extern Type::atype_t* StringLength(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* StringRead(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* StringWrite(FuncParams params, Interpreter& vm, const Lexeme& caller);
			}
		}
	}
}

#pragma warning(pop)