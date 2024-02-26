#include "BuiltInFunctions.h"

#include "Types/AstralTypes.h"

Astral::Type::atype_t* Astral::Functions::Astral::IO::PrintFunction(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	//If we do not know the type we are printing, just print the address
	if (Type::void_t* void_t = dynamic_cast<Type::void_t*>(params[0]))
	{
		Error("void reference", caller);
		vm.Fail();
		return nullptr;
	}
	else
		std::cout << params[0]->ToString();

    return nullptr;
}

Astral::Type::atype_t* Astral::Functions::Astral::IO::PrintlnFunction(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
    Type::atype_t* ret = PrintFunction(params, vm, caller);
    std::cout << '\n';
    return ret;
}

Astral::Type::atype_t* Astral::Functions::Astral::String::StringLength(FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::String::StringRead(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	//Validate input types
	Type::string_t* str = dynamic_cast<Type::string_t*>(params[0]);
	Type::number_t* index = dynamic_cast<Type::number_t*>(params[1]);
	if (!str)
	{
		Error("Expected string", caller);
		vm.Fail();
		return nullptr;
	}
	if (!index)
	{
		Error("Expected numeric index", caller);
		vm.Fail();
		return nullptr;
	}

	int i = (int)index->Value();
	int len = (int)strlen(str->Value());
	if (i >= len)
	{
		Error("Index was out of range", caller);
		vm.Fail();
		return nullptr;
	}

	std::string v = std::string(1, str->Value()[i]);
	return new Type::string_t(v);
}

Astral::Type::atype_t* Astral::Functions::Astral::String::StringWrite(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::string_t* str = dynamic_cast<Type::string_t*>(params[0]);

	//If we have a string copy, we should warn the programmer
	if (str)
		Warning("String was passed by value. No changes will be made", caller);

	Type::number_t* index = dynamic_cast<Type::number_t*>(params[1]);
	Type::string_t* val = dynamic_cast<Type::string_t*>(params[2]); ///@todo Change to char type when implemented. For now ensure 1 length string

	Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]);
	if (ref)
		str = dynamic_cast<Type::string_t*>(ref->GetBlock()->data);

	if (!str)
	{
		Error("Expected string", caller);
		vm.Fail();
		return nullptr;
	}
	if (!index)
	{
		Error("Expected numeric index", caller);
		vm.Fail();
		return nullptr;
	}
	if (!val || strlen(val->Value()) != 1)
	{
		Error("Expected 1-length string");
		vm.Fail();
		return nullptr;
	}

	int i = (int)index->Value();
	int len = (int)strlen(str->Value());
	if (i >= len)
	{
		Error("Index was out of range", caller);
		vm.Fail();
		return nullptr;
	}

	str->EditableValue()[i] = val->Value()[0];
	return nullptr;
}

Astral::Type::atype_t* Astral::Functions::Astral::IO::Input(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	std::string str;
	std::getline(std::cin, str);
	return new Type::string_t(str);
}

Astral::Type::atype_t* Astral::Functions::Astral::GetType(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	return new Type::string_t(params[0]->Type().c_str());
}

Astral::Type::atype_t* Astral::Functions::Astral::CreateVoid(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	return new Type::void_t();
}