#include "BuiltInFunctions.h"

#include "Types/AstralTypes.h"

inline static float lerp(float a, float b, float c)
{
	return a * (1.0f - c) + (b * c);
}

inline static float sign(float x)
{
	return (float)((0.f < x) - (x < 0.f));
}

inline static float clamp(float min, float max, float v)
{
	return (std::max)(min, (std::min)(v, max));
}

Astral::Type::atype_t* Astral::Functions::Astral::IO::PrintFunction(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::IO::PrintlnFunction(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
    Type::atype_t* ret = PrintFunction(params, vm, caller);
    std::cout << '\n';
    return ret;
}

Astral::Type::atype_t* Astral::Functions::Astral::String::StringLength(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::String::StringRead(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::String::StringWrite(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::String::BinaryFromNumber(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::string_t(std::bitset<32>((int)num->Value()).to_string());
}

Astral::Type::atype_t* Astral::Functions::Astral::String::BinaryFromNumberW(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	Type::number_t* count = dynamic_cast<Type::number_t*>(params[1]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[1]))
		count = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num || !count)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	int v = (int)num->Value();
	int c = (int)count->Value();

	std::vector<bool> bits;
	for (int i = 0; i < c; ++i)
	{
		bits.push_back(v & 1);
		v >>= 1;
	}

	std::string res;
	for (int i = c - 1; i >= 0; i--)
		res += std::to_string(bits[i]);

	return new Type::string_t(res);
}

Astral::Type::atype_t* Astral::Functions::Astral::IO::Input(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	std::string str;
	std::getline(std::cin, str);
	return new Type::string_t(str);
}

Astral::Type::atype_t* Astral::Functions::Astral::IO::Clear(const FuncParams param, Interpreter& vm, const Lexeme& caller)
{
#ifdef _WIN32
	///@see https://stackoverflow.com/questions/5866529/how-do-we-clear-the-console-in-assembly/5866648#5866648
	COORD tl{ 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD cells = s.dwSize.X * s.dwSize.Y;
	DWORD written;
	FillConsoleOutputCharacterW(console, L' ', cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
#else
	Error("Clear is currently only supported on Windows", caller);
	vm.Fail();
#endif

	return nullptr;
}

Astral::Type::atype_t* Astral::Functions::Astral::IO::Title(const FuncParams param, Interpreter& vm, const Lexeme& caller)
{
#ifdef _WIN32
	SetConsoleTitleA(param[0]->ToString().c_str());
#else
	Error("Title is currently only supported on Windows", caller);
	vm.Fail();
#endif

	return nullptr;
}

Astral::Type::atype_t* Astral::Functions::Astral::GetType(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	return new Type::string_t(params[0]->Type().c_str());
}

Astral::Type::atype_t* Astral::Functions::Astral::CreateVoid(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	return new Type::void_t();
}

Astral::Type::atype_t* Astral::Functions::Astral::ToNumber(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::string_t* str = dynamic_cast<Type::string_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		str = dynamic_cast<Type::string_t*>(ref->GetBlock()->data);

	if (!str)
	{
		Error("Expected string", caller);
		return nullptr;
	}

	return new Type::number_t(std::stof(str->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::New(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::string_t* str = dynamic_cast<Type::string_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		str = dynamic_cast<Type::string_t*>(ref->GetBlock()->data);

	if (!str)
	{
		Error("Expected string", caller);
		return nullptr;
	}

	const char* structName = str->Value();
	const std::vector<Rom::StructDefinition>& structs = vm.GetRom().GetStructs();

	const Rom::StructDefinition* tmplate = nullptr;
	for (const Rom::StructDefinition& str : structs)
	{
		if (strcmp(structName, str.name) == 0)
		{
			tmplate = &str;
			break;
		}
	}

	if (!tmplate)
	{
		std::string msg = "Struct '" + std::string(structName) + "' could not be found";
		Error(msg.c_str(), caller);
	}

	Warning("Structs currently have a memory-leak and SHOULD NOT be used", caller);

	Type::struct_t* _struct = new Type::struct_t(tmplate->members);
	return _struct;
}

Astral::Type::atype_t* Astral::Functions::Astral::GetMember(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::struct_t* str = dynamic_cast<Type::struct_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		str = dynamic_cast<Type::struct_t*>(ref->GetBlock()->data);

	if (!str)
	{
		Error("Expected struct", caller);
		return nullptr;
	}

	Type::string_t* member = dynamic_cast<Type::string_t*>(params[1]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[1]))
		member = dynamic_cast<Type::string_t*>(ref->GetBlock()->data);

	if (!member)
	{
		Error("Expected string", caller);
		return nullptr;
	}

	if (!str->HasMember(member->Value()))
	{
		Error((std::string("Struct does not have member '") + member->Value() + '\'').c_str());
		return nullptr;
	}

	return *str->GetMember(member->Value());
}

Astral::Type::atype_t* Astral::Functions::Astral::SetMember(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::struct_t* str = dynamic_cast<Type::struct_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		str = dynamic_cast<Type::struct_t*>(ref->GetBlock()->data);

	if (!str)
	{
		Error("Expected struct", caller);
		return nullptr;
	}

	Type::string_t* member = dynamic_cast<Type::string_t*>(params[1]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[1]))
		member = dynamic_cast<Type::string_t*>(ref->GetBlock()->data);

	if (!member)
	{
		Error("Expected string", caller);
		return nullptr;
	}

	if (!str->HasMember(member->Value()))
	{
		Error((std::string("Struct does not have member '") + member->Value() + '\'').c_str());
		return nullptr;
	}

	Type::atype_t* oldValue = *str->GetMember(member->Value());
	oldValue->isOnStack = false;
	GarbageCollector::Instance().RegisterDanglingPointer(oldValue);

	Type::atype_t* newValue = params[2]->Copy();
	*str->GetMember(member->Value()) = newValue;

	return new Type::void_t();
}

Astral::Type::atype_t* Astral::Functions::Astral::ToString(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	return new Type::string_t(params[0]->ToString());
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Sin(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Cos(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Tan(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::ASin(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::ACos(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::ATan(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::ATan2(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Sqrt(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Log(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Abs(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Floor(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Ceil(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Round(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Clamp(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Min(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Max(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Lerp(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Sign(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

Astral::Type::atype_t* Astral::Functions::Astral::Math::Rad(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(num->Value() * 3.1415936f / 180.f);
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Deg(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* num = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		num = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!num)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t(num->Value() * 180.f / 3.1415936f);
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::And(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

	return new Type::number_t((float)((int)a->Value() & (int)b->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Or(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

	return new Type::number_t((float)((int)a->Value() | (int)b->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Xor(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

	return new Type::number_t((float)((int)a->Value() ^ (int)b->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::Not(const FuncParams params, Interpreter& vm, const Lexeme& caller)
{
	Type::number_t* a = dynamic_cast<Type::number_t*>(params[0]);
	if (Type::ref_t* ref = dynamic_cast<Type::ref_t*>(params[0]))
		a = dynamic_cast<Type::number_t*>(ref->GetBlock()->data);

	if (!a)
	{
		Error("Expected numeric value", caller);
		return nullptr;
	}

	return new Type::number_t((float)(~(int)a->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::LeftShift(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

	return new Type::number_t((float)((int)a->Value() << (int)b->Value()));
}

Astral::Type::atype_t* Astral::Functions::Astral::Math::RightShift(const FuncParams params, Interpreter& vm, const Lexeme& caller)
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

	return new Type::number_t((float)((int)a->Value() >> (int)b->Value()));
}