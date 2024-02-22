#include "BuiltInFunctions.h"

#include "Types/AstralTypes.h"

Astral::Type::atype_t* Astral::PrintFunction(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller)
{
	//If we do not know the type we are printing, just print the address
	if (Type::number_t* number_t = dynamic_cast<Type::number_t*>(params[0]))
		std::cout << number_t->Value();
	else if (Type::string_t* string_t = dynamic_cast<Type::string_t*>(params[0]))
		std::cout << string_t->Value();
	else if (Type::func_t* func = dynamic_cast<Type::func_t*>(params[0]))
		std::cout << "<ASTRAL-FUNCTION>";
	else if (Type::externfunc_t* extrn = dynamic_cast<Type::externfunc_t*>(params[0]))
		std::cout << "<EXTERN-FUNCTION>";
	else if (Type::void_t* void_t = dynamic_cast<Type::void_t*>(params[0]))
	{
		Error("void reference", caller);
		vm.Fail();
		return nullptr;
	}
	else
		std::cout << '$' << params[0];

    return nullptr;
}

Astral::Type::atype_t* Astral::PrintlnFunction(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller)
{
    Type::atype_t* ret = PrintFunction(params, vm, caller);
    std::cout << '\n';
    return ret;
}

Astral::Type::atype_t* Astral::CreateVoid(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller)
{
	return new Type::void_t();
}

Astral::Type::atype_t* Astral::StringLength(const std::vector<Type::atype_t*>& params, Interpreter& vm, const Lexeme& caller)
{
	Type::string_t* str;
	if (str = dynamic_cast<Type::string_t*>(params[0]))
		return new Type::number_t((float)strlen(str->Value()));
	else
	{
		Error("Expected a string to be passed", caller);
		vm.Fail();
		return nullptr;
	}
}

void Astral::BindBuiltInFunctionsToInterpreter(Interpreter& interpreter)
{
	BindFunction __print("print", 1, PrintFunction);
	__print.Bind(interpreter);

	BindFunction __println("println", 1, PrintlnFunction);
	__println.Bind(interpreter);

	BindFunction __void("void", 0, CreateVoid);
	__void.Bind(interpreter);

	BindFunction __strlen("string_length", 1, StringLength);
	__strlen.Bind(interpreter);
}