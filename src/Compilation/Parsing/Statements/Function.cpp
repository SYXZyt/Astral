#include "Function.h"

void Astral::Function::Dump(int indent)
{
	std::cout << std::string(indent * 2, ' ') << "{ Function Definition }\n";
	parameters->Dump(indent + 1);
	funcBody->Dump(indent + 1);
}