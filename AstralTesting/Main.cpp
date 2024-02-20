#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <API.h>

Astral::Type::atype_t* MySuperCoolPrint(const std::vector<Astral::Type::atype_t*>& params)
{
	std::cout << "Hello =D\n";
	return nullptr;
}

int main(int, char**)
{
	Astral::SetGCLimit_Bytes(0);

	Astral::Rom program;
	if (!Astral::API::CompileFile("demo.ast", program, false, true, true))
		return 1;

	Astral::BindFunction func("Hello", 0, MySuperCoolPrint);


	Astral::Interpreter interpreter = Astral::API::CreateInterpreter(program);
	func.Bind(interpreter);

	Astral::API::RunInterpreter(interpreter);

	return 0;
}