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

			namespace Math
			{
				extern Type::atype_t* Sin(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Cos(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Tan(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* ASin(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* ACos(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* ATan(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* ATan2(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Sqrt(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Log(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Abs(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Floor(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Ceil(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Round(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Clamp(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Min(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Max(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Lerp(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Sign(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Rad(FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Deg(FuncParams params, Interpreter& vm, const Lexeme& caller);
			}
		}
	}
}

#pragma warning(pop)