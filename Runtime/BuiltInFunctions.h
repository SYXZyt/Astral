#pragma once
#pragma warning(push)
#pragma warning(disable : 4251)

#include "Interpreter.h"
#include "../Compilation/Tokenisation/Lexeme.h"

namespace Astral
{
	namespace Type { class Type::atype_t; }

	extern Type::atype_t* PrintFunction(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller);
	extern Type::atype_t* PrintlnFunction(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller);

	extern Type::atype_t* CreateVoid(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller);

	extern Type::atype_t* StringLength(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller);
	extern Type::atype_t* StringRead(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller);
	extern Type::atype_t* StringWrite(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller);

	extern ASTRAL void BindBuiltInFunctionsToInterpreter(Interpreter& interpreter);
}

#pragma warning(pop)