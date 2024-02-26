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

	astral_io.AddFunction(__print);
	astral_io.AddFunction(__println);
	astral_io.AddFunction(__input);

	libraries.push_back(astral_io);



	Library astral_string("astral.string");

	BindFunction __strlen("string_length", 1, Functions::Astral::String::StringLength);
	BindFunction __strread("string_read", 2, Functions::Astral::String::StringRead);
	BindFunction __strwrite("string_write", 3, Functions::Astral::String::StringWrite);

	astral_string.AddFunction(__strlen);
	astral_string.AddFunction(__strread);
	astral_string.AddFunction(__strwrite);

	libraries.push_back(astral_string);
}