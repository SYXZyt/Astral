#include "BuiltInFunctions.h"

#include "Types/AstralTypes.h"

inline static float lerp(float a, float b, float c)
{
	return a * (1.0 - c) + (b * c);
}

inline static float sign(float x)
{
	return (0 < x) - (x < 0);
}

inline static float clamp(float min, float max, float v)
{
	return (std::max)(min, (std::min)(v, max));
}

Astral::Type::atype_t* Astral::Functions::Astral::IO::PrintFunction(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Sin(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(sin(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Cos(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(cos(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Tan(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(tan(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::ASin(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(asin(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::ACos(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(acos(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::ATan(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(atan(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::ATan2(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* a = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		a = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	Type::number_t* b = dynamic_cast<Type::number_t*>(params[1]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[1]))
		b = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!a || !b)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(atan2(a->Value(), b->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Sqrt(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(sqrt(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Log(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(log(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Abs(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(abs(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Floor(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(floor(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Ceil(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(ceil(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Round(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(round(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Clamp(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* a = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		a = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	Type::number_t* b = dynamic_cast<Type::number_t*>(params[1]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[1]))
		b = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	Type::number_t* c = dynamic_cast<Type::number_t*>(params[2]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[2]))
		c = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!a || !b || !c)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(clamp(a->Value(), b->Value(), c->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Min(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* a = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		a = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	Type::number_t* b = dynamic_cast<Type::number_t*>(params[1]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[1]))
		b = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!a || !b)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t((std::min)(a->Value(), b->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Max(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* a = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		a = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	Type::number_t* b = dynamic_cast<Type::number_t*>(params[1]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[1]))
		b = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!a || !b)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t((std::max)(a->Value(), b->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Lerp(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* a = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		a = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	Type::number_t* b = dynamic_cast<Type::number_t*>(params[1]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[1]))
		b = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	Type::number_t* c = dynamic_cast<Type::number_t*>(params[2]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[2]))
		c = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!a || !b || !c)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(lerp(a->Value(), b->Value(), c->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Sign(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(sign(num->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Rad(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(num->Value() * 3.1415936 / 180);
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Deg(FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(num->Value() * 180 / 3.1415936);
}