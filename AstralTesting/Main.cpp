#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <API.h>

int main(int, char**)
{
	Astral::SetGCLimit_Bytes(0);

	Astral::Rom program;
	if (!Astral::API::CompileFile("demo.ast", program, false, true, true))
		return 1;

	Astral::Interpreter interpreter = Astral::API::CreateInterpreter(program);
	
	Astral::BindBuiltInFunctionsToInterpreter(interpreter);

	interpreter.CallFunction("Main");

	return 0;
}