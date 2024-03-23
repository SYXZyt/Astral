#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include <bitset>

#include "Interpreter.h"
#include "../Compilation/Tokenisation/Lexeme.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace Astral
{
	namespace Type { class atype_t; }

	namespace Functions
	{
		namespace Astral
		{
			extern Type::atype_t* GetType(const FuncParams params, Interpreter& vm, const Lexeme& caller);
			extern Type::atype_t* CreateVoid(const FuncParams params, Interpreter& vm, const Lexeme& caller);
			extern Type::atype_t* ToNumber(const FuncParams params, Interpreter& vm, const Lexeme& caller);
			extern Type::atype_t* New(const FuncParams params, Interpreter& vm, const Lexeme& caller);
			extern Type::atype_t* GetMember(const FuncParams params, Interpreter& vm, const Lexeme& caller);
			extern Type::atype_t* SetMember(const FuncParams params, Interpreter& vm, const Lexeme& caller);
			extern Type::atype_t* ToString(const FuncParams params, Interpreter& vm, const Lexeme& caller);

			namespace IO
			{
				extern Type::atype_t* PrintFunction(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* PrintlnFunction(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Input(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Clear(const FuncParams param, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Title(const FuncParams param, Interpreter& vm, const Lexeme& caller);
			}

			namespace String
			{
				extern Type::atype_t* StringLength(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* StringRead(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* StringWrite(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* BinaryFromNumber(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* BinaryFromNumberW(const FuncParams params, Interpreter& vm, const Lexeme& caller);
			}

			namespace Math
			{
				extern Type::atype_t* Sin(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Cos(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Tan(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* ASin(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* ACos(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* ATan(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* ATan2(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Sqrt(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Log(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Abs(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Floor(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Ceil(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Round(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Clamp(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Min(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Max(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Lerp(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Sign(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Rad(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Deg(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* And(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Or(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Xor(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* Not(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* LeftShift(const FuncParams params, Interpreter& vm, const Lexeme& caller);
				extern Type::atype_t* RightShift(const FuncParams params, Interpreter& vm, const Lexeme& caller);
			}
		}
	}
}

#pragma warning(pop)