#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <src/API.h>

int main(int, char**)
{	
	Astral::Rom program;
	if (!Astral::API::CompileFile("demo.ast", program, false, !false, false))
		return 1;

	Astral::API::LoadDefaultLibraries();

	Astral::Interpreter interpreter = Astral::API::CreateInterpreter(program);
	Astral::API::MainCall(interpreter);

	return 0;
}