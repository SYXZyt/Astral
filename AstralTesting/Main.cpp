#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <API.h>

int main(int, char**)
{
	//Astral::SetGCLimit_Bytes(1024 * 1024);
	Astral::SetGCLimit_Bytes(0);

	Astral::API::rom program;
	if (!Astral::API::CompileFile("demo.ast", program, false, true, true))
		return 1;

	Astral::API::ExecuteScript(program);
	return 0;
}