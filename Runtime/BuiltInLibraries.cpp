#include "BuiltInLibraries.h"

std::vector<Astral::Library> Astral::libraries = std::vector<Astral::Library>();

void Astral::LoadLibraries()
{
	Library astral("astral");
	
	BindFunction __type("get_type", 1, Functions::Astral::GetType);
	BindFunction __void("void", 0, Functions::Astral::CreateVoid);

	astral.AddFunction(__type);
	astral.AddFunction(__void);

	libraries.push_back(astral);



	Library astral_io("astral.io");

	BindFunction __print("print", 1, Functions::Astral::IO::PrintFunction);
	BindFunction __println("println", 1, Functions::Astral::IO::PrintlnFunction);
	BindFunction __input("input", 1, Functions::Astral::IO::Input);
	BindFunction __clear("clear", 0, Functions::Astral::IO::Clear);
	BindFunction __title("title", 1, Functions::Astral::IO::Title);

	astral_io.AddFunction(__print);
	astral_io.AddFunction(__println);
	astral_io.AddFunction(__input);
	astral_io.AddFunction(__clear);
	astral_io.AddFunction(__title);

	libraries.push_back(astral_io);



	Library astral_string("astral.string");

	BindFunction __strlen("string_length", 1, Functions::Astral::String::StringLength);
	BindFunction __strread("string_read", 2, Functions::Astral::String::StringRead);
	BindFunction __strwrite("string_write", 3, Functions::Astral::String::StringWrite);

	astral_string.AddFunction(__strlen);
	astral_string.AddFunction(__strread);
	astral_string.AddFunction(__strwrite);

	libraries.push_back(astral_string);



	Library astral_math("astral.math");

	BindFunction __sin("sin", 1, Functions::Astral::Math::Sin);
	BindFunction __cos("cos", 1, Functions::Astral::Math::Cos);
	BindFunction __tan("tan", 1, Functions::Astral::Math::Tan);
	BindFunction __asin("asin", 1, Functions::Astral::Math::ASin);
	BindFunction __acos("acos", 1, Functions::Astral::Math::ACos);
	BindFunction __atan("atan", 1, Functions::Astral::Math::ATan);
	BindFunction __atan2("atan2", 2, Functions::Astral::Math::ATan2);
	BindFunction __sqrt("sqrt", 1, Functions::Astral::Math::Sqrt);
	BindFunction __log("log", 1, Functions::Astral::Math::Log);
	BindFunction __abs("abs", 1, Functions::Astral::Math::Abs);
	BindFunction __floor("floor", 1, Functions::Astral::Math::Floor);
	BindFunction __ceil("ceil", 1, Functions::Astral::Math::Ceil);
	BindFunction __round("round", 1, Functions::Astral::Math::Round);
	BindFunction __clamp("clamp", 3, Functions::Astral::Math::Clamp);
	BindFunction (__min) /*<-- thank you for this Microsoft */("min", 1, Functions::Astral::Math::Min);
	BindFunction (__max)("max", 1, Functions::Astral::Math::Max);
	BindFunction __lerp("lerp", 3, Functions::Astral::Math::Lerp);
	BindFunction __sign("sign", 1, Functions::Astral::Math::Sign);
	BindFunction __rad("rad", 1, Functions::Astral::Math::Rad);
	BindFunction __deg("deg", 1, Functions::Astral::Math::Deg);

	astral_math.AddFunction(__sin);
	astral_math.AddFunction(__cos);
	astral_math.AddFunction(__tan);
	astral_math.AddFunction(__asin);
	astral_math.AddFunction(__acos);
	astral_math.AddFunction(__atan);
	astral_math.AddFunction(__atan2);
	astral_math.AddFunction(__sqrt);
	astral_math.AddFunction(__log);
	astral_math.AddFunction(__abs);
	astral_math.AddFunction(__floor);
	astral_math.AddFunction(__ceil);
	astral_math.AddFunction(__round);
	astral_math.AddFunction(__clamp);
	astral_math.AddFunction(__min);
	astral_math.AddFunction(__max);
	astral_math.AddFunction(__lerp);
	astral_math.AddFunction(__sign);
	astral_math.AddFunction(__rad);
	astral_math.AddFunction(__deg);

	libraries.push_back(astral_math);
}